#ifndef TOMATKERNEL_RSDT_H
#define TOMATKERNEL_RSDT_H

#include <elf64.h>

typedef struct sdt_hdr {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char oemid[6];
    char oem_table_id[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
} sdt_hdr_t;

typedef struct rsdt {
    sdt_hdr_t header;
    uint32_t sdts[0];
} rsdt_t;

typedef struct xsdt {
    sdt_hdr_t header;
    uint64_t sdts[0];
} xsdt_t;

extern rsdt_t rsdt;
extern xsdt_t xsdt;

/**
 * Will search for an sdt inside the rsdt
 *
 * @remark
 * Will search either rsdt or xsdt as needed
 */
sdt_hdr_t* rsdt_search(char* signature);

#endif //TOMATKERNEL_RSDT_H
