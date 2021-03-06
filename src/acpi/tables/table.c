#include <util/trace.h>
#include <mm/vmm.h>

#include "table.h"

void trace_table(acpi_header_t* header) {
    TRACE("\t%4.4s 0x%016lx %08x (v%02x %6.6s %8.8s %08x %4.4s %08x)",
            header->signature,
            (uintptr_t)DIRECT_TO_PHYSICAL(header),
            header->length,
            header->revision,
            header->oem,
            header->oem_table,
            header->oem_revision,
            header->creator_id,
            header->creator_revision);
}
