#include "rsdt.h"
#include "rsdp.h"
#include "drivers/acpi/acpi.h"

#include <logger/logger.h>
#include <memory/vmm.h>

#include <stddef.h>
#include <string.h>

rsdt_t* rsdt;
xsdt_t* xsdt;

error_t rsdt_init() {
    error_t err = NO_ERROR;
    sdt_hdr_t* hdr;

    if(rsdp->revision == 0) {
        rsdt = (rsdt_t *) PHYSICAL_ADDRESS(rsdp->rsdt_addr);
        hdr = &rsdt->header;
        if(!vmm_is_mapped(kernel_address_space, (uintptr_t) rsdt)) {
            CHECK_AND_RETHROW(vmm_map(kernel_address_space, rsdt, (void*)(uintptr_t)rsdp->rsdt_addr, 0));
        }

        log_info("\tRSDT found (0x%016p)", (uintptr_t)rsdt - PHYSICAL_BASE);
    }else {
        xsdt = (xsdt_t *) PHYSICAL_ADDRESS(rsdp2->xsdt_addr);
        hdr = &xsdt->header;
        if(!vmm_is_mapped(kernel_address_space, (uintptr_t) xsdt)) {
            CHECK_AND_RETHROW(vmm_map(kernel_address_space, xsdt, (void*)(uintptr_t)rsdp2->xsdt_addr, 0));
        }


        if(rsdp->revision != 2) {
            log_warn("\tUnknown ACPI revision, assuming XSDT");
        }

        log_info("\tXSDT found (0x%016p)", (uintptr_t)xsdt - PHYSICAL_BASE);
    }

    CHECK_TRACE(acpi_validate_checksum(hdr, hdr->length), "Invalid SDT checksum!");
    log_debug("\t\tRevision: %d", hdr->revision);
    log_debug("\t\tOEM ID: %c%c%c%c%c%c"
                        , hdr->oemid[0]
                        , hdr->oemid[1]
                        , hdr->oemid[2]
                        , hdr->oemid[3]
                        , hdr->oemid[4]
                        , hdr->oemid[5]);
    log_debug("\t\tOEM TABLE ID: %c%c%c%c%c%c%c%c"
                        , hdr->oem_table_id[0]
                        , hdr->oem_table_id[1]
                        , hdr->oem_table_id[2]
                        , hdr->oem_table_id[3]
                        , hdr->oem_table_id[4]
                        , hdr->oem_table_id[5]
                        , hdr->oem_table_id[6]
                        , hdr->oem_table_id[7]);


    // just for debugging
    log_debug("\t\tentries:");
    if(rsdt != NULL) {
        // rsdt iteration
        for(uint32_t* sdt = rsdt->sdts; sdt < (rsdt->sdts + ((rsdt->header.length - sizeof(sdt_hdr_t)) / 4)); sdt++) {
            hdr = (sdt_hdr_t *) PHYSICAL_ADDRESS(*sdt);
            if(!vmm_is_mapped(kernel_address_space, (uintptr_t) hdr)) {
                CHECK_AND_RETHROW(vmm_map(kernel_address_space, hdr, (void*)(uintptr_t)*sdt, 0));
            }
            log_debug("\t\t\t%c%c%c%c"
                , hdr->signature[0]
                , hdr->signature[1]
                , hdr->signature[2]
                , hdr->signature[3]);
        }
    }else {
        // xsdt iteration
        for(uint64_t* sdt = xsdt->sdts; sdt < (xsdt->sdts + ((xsdt->header.length - sizeof(sdt_hdr_t)) / 8)); sdt++) {
            hdr = (sdt_hdr_t *) PHYSICAL_ADDRESS(*sdt);
            if(!vmm_is_mapped(kernel_address_space, (uintptr_t) hdr)) {
                CHECK_AND_RETHROW(vmm_map(kernel_address_space, hdr, (void*)(uintptr_t)*sdt, 0));
            }
            log_debug("\t\t\t%c%c%c%c"
                , hdr->signature[0]
                , hdr->signature[1]
                , hdr->signature[2]
                , hdr->signature[3]);
        }
    }


    CHECK_ERROR_TRACE(rsdt || xsdt, ERROR_NOT_FOUND, "Could not find xsdt/rsdt!");
cleanup:
    return err;
}

sdt_hdr_t* xsdt_search(char* signature) {
    for(uint64_t* sdt = xsdt->sdts; sdt < (xsdt->sdts + ((xsdt->header.length - sizeof(sdt_hdr_t)) / 8)); sdt++) {
        sdt_hdr_t* hdr = (sdt_hdr_t *) PHYSICAL_ADDRESS(*sdt);
        if(memcmp(hdr->signature, signature, 4) == 0) {
            return hdr;
        }
    }

    return NULL;
}

sdt_hdr_t* rsdt_search(char* signature) {
    if(rsdt != NULL) {
        // rsdt searching
        for(uint32_t* sdt = rsdt->sdts; sdt < (rsdt->sdts + ((rsdt->header.length - sizeof(sdt_hdr_t)) / 4)); sdt++) {
            sdt_hdr_t* hdr = (sdt_hdr_t *) PHYSICAL_ADDRESS(*sdt);
            if(memcmp(hdr->signature, signature, 4) == 0) {
                return hdr;
            }
        }
    }else {
        // xsdt searching
        return xsdt_search(signature);
    }

    // not found
    return NULL;
}