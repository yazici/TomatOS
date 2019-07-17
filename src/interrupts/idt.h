#ifndef KRETLIM_KERNEL_IDT_H
#define KRETLIM_KERNEL_IDT_H

#include <stdint.h>

#define IDT_TYPE_TASK           0x5
#define IDT_TYPE_INTERRUPT_16   0x6
#define IDT_TYPE_TRAP_16        0x7
#define IDT_TYPE_INTERRUPT_32   0xE
#define IDT_TYPE_TRAP_32        0xF

typedef struct idt_entry {
    uint64_t handler_low : 16;
    uint64_t selector : 16;
    uint64_t ist : 3;
    uint64_t _zero1 : 5;
    uint64_t gate_type : 4;
    uint64_t _zero2 : 1;
    uint64_t ring : 2;
    uint64_t present : 1;
    uint64_t handler_high : 48;
    uint64_t _zero3 : 32;
} __attribute__((packed)) idt_entry_t;

typedef struct idt {
    uint16_t limit;
    idt_entry_t* base;
} __attribute__((packed)) idt_t;

/**
 * This will set all the stub handlers
 */
void idt_init();

#endif //KRETLIM_KERNEL_IDT_H
