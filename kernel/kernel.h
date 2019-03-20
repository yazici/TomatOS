#ifndef TOMATKERNEL_KERNEL_H
#define TOMATKERNEL_KERNEL_H

#include "common/multiboot.h"

/**
 * The kernel entry point
 *
 * Note: This function assumes we are already in long mode 64bit and have the first
 *       1GB identity mapped
 */
void kernel_main(multiboot_info_t* info);

#endif //TOMATKERNEL_KERNEL_H
