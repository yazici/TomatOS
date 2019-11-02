#include <stddef.h>
#include <stdbool.h>

#include <memory/gdt.h>
#include <util/arch.h>

#include "isrs.h"
#include "idt.h"

static idt_entry_t idt_entries[0xFF + 1];

idt_t idt = {
        .limit = sizeof(idt_entries),
        .base = idt_entries
};

static void set_idt_entry(uint8_t i, void(*handler)(), int ist) {
    idt_entries[i].handler_low = (uint16_t) ((uintptr_t)handler & 0xFFFF);
    idt_entries[i].handler_high = (uint64_t) ((uintptr_t)handler >> 16);
    idt_entries[i].gate_type = IDT_TYPE_INTERRUPT_32;
    idt_entries[i].selector = GDT_KERNEL_CODE;
    idt_entries[i].present = true;
    idt_entries[i].ring = 0;
    idt_entries[i].ist = (uint64_t) ist;
}

void idt_post_tss() {
    /*
     * IST:
     *  - 1: most exceptions
     *  - 2: NMI
     *  - 3: Page Fault
     */
    set_idt_entry(0x00,handle_interrupt_request_00, 1);
    set_idt_entry(0x01,handle_interrupt_request_01, 1);
    set_idt_entry(0x02,handle_interrupt_request_02, 2);
    set_idt_entry(0x03,handle_interrupt_request_03, 1);
    set_idt_entry(0x04,handle_interrupt_request_04, 1);
    set_idt_entry(0x05,handle_interrupt_request_05, 1);
    set_idt_entry(0x06,handle_interrupt_request_06, 1);
    set_idt_entry(0x07,handle_interrupt_request_07, 1);
    set_idt_entry(0x08,handle_interrupt_request_08, 1);
    set_idt_entry(0x09,handle_interrupt_request_09, 1);
    set_idt_entry(0x0a,handle_interrupt_request_0a, 1);
    set_idt_entry(0x0b,handle_interrupt_request_0b, 1);
    set_idt_entry(0x0c,handle_interrupt_request_0c, 1);
    set_idt_entry(0x0d,handle_interrupt_request_0d, 1);
    set_idt_entry(0x0e,handle_interrupt_request_0e, 3);
    set_idt_entry(0x0f,handle_interrupt_request_0f, 1);
    set_idt_entry(0x10,handle_interrupt_request_10, 1);
    set_idt_entry(0x11,handle_interrupt_request_11, 1);
    set_idt_entry(0x12,handle_interrupt_request_12, 1);
    set_idt_entry(0x13,handle_interrupt_request_13, 1);
    set_idt_entry(0x14,handle_interrupt_request_14, 1);
    set_idt_entry(0x15,handle_interrupt_request_15, 1);
    set_idt_entry(0x16,handle_interrupt_request_16, 1);
    set_idt_entry(0x17,handle_interrupt_request_17, 1);
    set_idt_entry(0x18,handle_interrupt_request_18, 1);
    set_idt_entry(0x19,handle_interrupt_request_19, 1);
    set_idt_entry(0x1a,handle_interrupt_request_1a, 1);
    set_idt_entry(0x1b,handle_interrupt_request_1b, 1);
    set_idt_entry(0x1c,handle_interrupt_request_1c, 1);
    set_idt_entry(0x1d,handle_interrupt_request_1d, 1);
    set_idt_entry(0x1e,handle_interrupt_request_1e, 1);
    set_idt_entry(0x1f,handle_interrupt_request_1f, 1);
    set_idt_entry(0x20,handle_interrupt_request_20, 1);
}

void idt_init() {
    set_idt_entry(0x00,handle_interrupt_request_00, 0);
    set_idt_entry(0x01,handle_interrupt_request_01, 0);
    set_idt_entry(0x02,handle_interrupt_request_02, 0);
    set_idt_entry(0x03,handle_interrupt_request_03, 0);
    set_idt_entry(0x04,handle_interrupt_request_04, 0);
    set_idt_entry(0x05,handle_interrupt_request_05, 0);
    set_idt_entry(0x06,handle_interrupt_request_06, 0);
    set_idt_entry(0x07,handle_interrupt_request_07, 0);
    set_idt_entry(0x08,handle_interrupt_request_08, 0);
    set_idt_entry(0x09,handle_interrupt_request_09, 0);
    set_idt_entry(0x0a,handle_interrupt_request_0a, 0);
    set_idt_entry(0x0b,handle_interrupt_request_0b, 0);
    set_idt_entry(0x0c,handle_interrupt_request_0c, 0);
    set_idt_entry(0x0d,handle_interrupt_request_0d, 0);
    set_idt_entry(0x0e,handle_interrupt_request_0e, 0);
    set_idt_entry(0x0f,handle_interrupt_request_0f, 0);
    set_idt_entry(0x10,handle_interrupt_request_10, 0);
    set_idt_entry(0x11,handle_interrupt_request_11, 0);
    set_idt_entry(0x12,handle_interrupt_request_12, 0);
    set_idt_entry(0x13,handle_interrupt_request_13, 0);
    set_idt_entry(0x14,handle_interrupt_request_14, 0);
    set_idt_entry(0x15,handle_interrupt_request_15, 0);
    set_idt_entry(0x16,handle_interrupt_request_16, 0);
    set_idt_entry(0x17,handle_interrupt_request_17, 0);
    set_idt_entry(0x18,handle_interrupt_request_18, 0);
    set_idt_entry(0x19,handle_interrupt_request_19, 0);
    set_idt_entry(0x1a,handle_interrupt_request_1a, 0);
    set_idt_entry(0x1b,handle_interrupt_request_1b, 0);
    set_idt_entry(0x1c,handle_interrupt_request_1c, 0);
    set_idt_entry(0x1d,handle_interrupt_request_1d, 0);
    set_idt_entry(0x1e,handle_interrupt_request_1e, 0);
    set_idt_entry(0x1f,handle_interrupt_request_1f, 0);
    set_idt_entry(0x20,handle_interrupt_request_20, 0);
    set_idt_entry(0x21,handle_interrupt_request_21, 0);
    set_idt_entry(0x22,handle_interrupt_request_22, 0);
    set_idt_entry(0x23,handle_interrupt_request_23, 0);
    set_idt_entry(0x24,handle_interrupt_request_24, 0);
    set_idt_entry(0x25,handle_interrupt_request_25, 0);
    set_idt_entry(0x26,handle_interrupt_request_26, 0);
    set_idt_entry(0x27,handle_interrupt_request_27, 0);
    set_idt_entry(0x28,handle_interrupt_request_28, 0);
    set_idt_entry(0x29,handle_interrupt_request_29, 0);
    set_idt_entry(0x2a,handle_interrupt_request_2a, 0);
    set_idt_entry(0x2b,handle_interrupt_request_2b, 0);
    set_idt_entry(0x2c,handle_interrupt_request_2c, 0);
    set_idt_entry(0x2d,handle_interrupt_request_2d, 0);
    set_idt_entry(0x2e,handle_interrupt_request_2e, 0);
    set_idt_entry(0x2f,handle_interrupt_request_2f, 0);
    set_idt_entry(0x30,handle_interrupt_request_30, 0);
    set_idt_entry(0x31,handle_interrupt_request_31, 0);
    set_idt_entry(0x32,handle_interrupt_request_32, 0);
    set_idt_entry(0x33,handle_interrupt_request_33, 0);
    set_idt_entry(0x34,handle_interrupt_request_34, 0);
    set_idt_entry(0x35,handle_interrupt_request_35, 0);
    set_idt_entry(0x36,handle_interrupt_request_36, 0);
    set_idt_entry(0x37,handle_interrupt_request_37, 0);
    set_idt_entry(0x38,handle_interrupt_request_38, 0);
    set_idt_entry(0x39,handle_interrupt_request_39, 0);
    set_idt_entry(0x3a,handle_interrupt_request_3a, 0);
    set_idt_entry(0x3b,handle_interrupt_request_3b, 0);
    set_idt_entry(0x3c,handle_interrupt_request_3c, 0);
    set_idt_entry(0x3d,handle_interrupt_request_3d, 0);
    set_idt_entry(0x3e,handle_interrupt_request_3e, 0);
    set_idt_entry(0x3f,handle_interrupt_request_3f, 0);
    set_idt_entry(0x40,handle_interrupt_request_40, 0);
    set_idt_entry(0x41,handle_interrupt_request_41, 0);
    set_idt_entry(0x42,handle_interrupt_request_42, 0);
    set_idt_entry(0x43,handle_interrupt_request_43, 0);
    set_idt_entry(0x44,handle_interrupt_request_44, 0);
    set_idt_entry(0x45,handle_interrupt_request_45, 0);
    set_idt_entry(0x46,handle_interrupt_request_46, 0);
    set_idt_entry(0x47,handle_interrupt_request_47, 0);
    set_idt_entry(0x48,handle_interrupt_request_48, 0);
    set_idt_entry(0x49,handle_interrupt_request_49, 0);
    set_idt_entry(0x4a,handle_interrupt_request_4a, 0);
    set_idt_entry(0x4b,handle_interrupt_request_4b, 0);
    set_idt_entry(0x4c,handle_interrupt_request_4c, 0);
    set_idt_entry(0x4d,handle_interrupt_request_4d, 0);
    set_idt_entry(0x4e,handle_interrupt_request_4e, 0);
    set_idt_entry(0x4f,handle_interrupt_request_4f, 0);
    set_idt_entry(0x50,handle_interrupt_request_50, 0);
    set_idt_entry(0x51,handle_interrupt_request_51, 0);
    set_idt_entry(0x52,handle_interrupt_request_52, 0);
    set_idt_entry(0x53,handle_interrupt_request_53, 0);
    set_idt_entry(0x54,handle_interrupt_request_54, 0);
    set_idt_entry(0x55,handle_interrupt_request_55, 0);
    set_idt_entry(0x56,handle_interrupt_request_56, 0);
    set_idt_entry(0x57,handle_interrupt_request_57, 0);
    set_idt_entry(0x58,handle_interrupt_request_58, 0);
    set_idt_entry(0x59,handle_interrupt_request_59, 0);
    set_idt_entry(0x5a,handle_interrupt_request_5a, 0);
    set_idt_entry(0x5b,handle_interrupt_request_5b, 0);
    set_idt_entry(0x5c,handle_interrupt_request_5c, 0);
    set_idt_entry(0x5d,handle_interrupt_request_5d, 0);
    set_idt_entry(0x5e,handle_interrupt_request_5e, 0);
    set_idt_entry(0x5f,handle_interrupt_request_5f, 0);
    set_idt_entry(0x60,handle_interrupt_request_60, 0);
    set_idt_entry(0x61,handle_interrupt_request_61, 0);
    set_idt_entry(0x62,handle_interrupt_request_62, 0);
    set_idt_entry(0x63,handle_interrupt_request_63, 0);
    set_idt_entry(0x64,handle_interrupt_request_64, 0);
    set_idt_entry(0x65,handle_interrupt_request_65, 0);
    set_idt_entry(0x66,handle_interrupt_request_66, 0);
    set_idt_entry(0x67,handle_interrupt_request_67, 0);
    set_idt_entry(0x68,handle_interrupt_request_68, 0);
    set_idt_entry(0x69,handle_interrupt_request_69, 0);
    set_idt_entry(0x6a,handle_interrupt_request_6a, 0);
    set_idt_entry(0x6b,handle_interrupt_request_6b, 0);
    set_idt_entry(0x6c,handle_interrupt_request_6c, 0);
    set_idt_entry(0x6d,handle_interrupt_request_6d, 0);
    set_idt_entry(0x6e,handle_interrupt_request_6e, 0);
    set_idt_entry(0x6f,handle_interrupt_request_6f, 0);
    set_idt_entry(0x70,handle_interrupt_request_70, 0);
    set_idt_entry(0x71,handle_interrupt_request_71, 0);
    set_idt_entry(0x72,handle_interrupt_request_72, 0);
    set_idt_entry(0x73,handle_interrupt_request_73, 0);
    set_idt_entry(0x74,handle_interrupt_request_74, 0);
    set_idt_entry(0x75,handle_interrupt_request_75, 0);
    set_idt_entry(0x76,handle_interrupt_request_76, 0);
    set_idt_entry(0x77,handle_interrupt_request_77, 0);
    set_idt_entry(0x78,handle_interrupt_request_78, 0);
    set_idt_entry(0x79,handle_interrupt_request_79, 0);
    set_idt_entry(0x7a,handle_interrupt_request_7a, 0);
    set_idt_entry(0x7b,handle_interrupt_request_7b, 0);
    set_idt_entry(0x7c,handle_interrupt_request_7c, 0);
    set_idt_entry(0x7d,handle_interrupt_request_7d, 0);
    set_idt_entry(0x7e,handle_interrupt_request_7e, 0);
    set_idt_entry(0x7f,handle_interrupt_request_7f, 0);
    set_idt_entry(0x80,handle_interrupt_request_80, 0);
    set_idt_entry(0x81,handle_interrupt_request_81, 0);
    set_idt_entry(0x82,handle_interrupt_request_82, 0);
    set_idt_entry(0x83,handle_interrupt_request_83, 0);
    set_idt_entry(0x84,handle_interrupt_request_84, 0);
    set_idt_entry(0x85,handle_interrupt_request_85, 0);
    set_idt_entry(0x86,handle_interrupt_request_86, 0);
    set_idt_entry(0x87,handle_interrupt_request_87, 0);
    set_idt_entry(0x88,handle_interrupt_request_88, 0);
    set_idt_entry(0x89,handle_interrupt_request_89, 0);
    set_idt_entry(0x8a,handle_interrupt_request_8a, 0);
    set_idt_entry(0x8b,handle_interrupt_request_8b, 0);
    set_idt_entry(0x8c,handle_interrupt_request_8c, 0);
    set_idt_entry(0x8d,handle_interrupt_request_8d, 0);
    set_idt_entry(0x8e,handle_interrupt_request_8e, 0);
    set_idt_entry(0x8f,handle_interrupt_request_8f, 0);
    set_idt_entry(0x90,handle_interrupt_request_90, 0);
    set_idt_entry(0x91,handle_interrupt_request_91, 0);
    set_idt_entry(0x92,handle_interrupt_request_92, 0);
    set_idt_entry(0x93,handle_interrupt_request_93, 0);
    set_idt_entry(0x94,handle_interrupt_request_94, 0);
    set_idt_entry(0x95,handle_interrupt_request_95, 0);
    set_idt_entry(0x96,handle_interrupt_request_96, 0);
    set_idt_entry(0x97,handle_interrupt_request_97, 0);
    set_idt_entry(0x98,handle_interrupt_request_98, 0);
    set_idt_entry(0x99,handle_interrupt_request_99, 0);
    set_idt_entry(0x9a,handle_interrupt_request_9a, 0);
    set_idt_entry(0x9b,handle_interrupt_request_9b, 0);
    set_idt_entry(0x9c,handle_interrupt_request_9c, 0);
    set_idt_entry(0x9d,handle_interrupt_request_9d, 0);
    set_idt_entry(0x9e,handle_interrupt_request_9e, 0);
    set_idt_entry(0x9f,handle_interrupt_request_9f, 0);
    set_idt_entry(0xa0,handle_interrupt_request_a0, 0);
    set_idt_entry(0xa1,handle_interrupt_request_a1, 0);
    set_idt_entry(0xa2,handle_interrupt_request_a2, 0);
    set_idt_entry(0xa3,handle_interrupt_request_a3, 0);
    set_idt_entry(0xa4,handle_interrupt_request_a4, 0);
    set_idt_entry(0xa5,handle_interrupt_request_a5, 0);
    set_idt_entry(0xa6,handle_interrupt_request_a6, 0);
    set_idt_entry(0xa7,handle_interrupt_request_a7, 0);
    set_idt_entry(0xa8,handle_interrupt_request_a8, 0);
    set_idt_entry(0xa9,handle_interrupt_request_a9, 0);
    set_idt_entry(0xaa,handle_interrupt_request_aa, 0);
    set_idt_entry(0xab,handle_interrupt_request_ab, 0);
    set_idt_entry(0xac,handle_interrupt_request_ac, 0);
    set_idt_entry(0xad,handle_interrupt_request_ad, 0);
    set_idt_entry(0xae,handle_interrupt_request_ae, 0);
    set_idt_entry(0xaf,handle_interrupt_request_af, 0);
    set_idt_entry(0xb0,handle_interrupt_request_b0, 0);
    set_idt_entry(0xb1,handle_interrupt_request_b1, 0);
    set_idt_entry(0xb2,handle_interrupt_request_b2, 0);
    set_idt_entry(0xb3,handle_interrupt_request_b3, 0);
    set_idt_entry(0xb4,handle_interrupt_request_b4, 0);
    set_idt_entry(0xb5,handle_interrupt_request_b5, 0);
    set_idt_entry(0xb6,handle_interrupt_request_b6, 0);
    set_idt_entry(0xb7,handle_interrupt_request_b7, 0);
    set_idt_entry(0xb8,handle_interrupt_request_b8, 0);
    set_idt_entry(0xb9,handle_interrupt_request_b9, 0);
    set_idt_entry(0xba,handle_interrupt_request_ba, 0);
    set_idt_entry(0xbb,handle_interrupt_request_bb, 0);
    set_idt_entry(0xbc,handle_interrupt_request_bc, 0);
    set_idt_entry(0xbd,handle_interrupt_request_bd, 0);
    set_idt_entry(0xbe,handle_interrupt_request_be, 0);
    set_idt_entry(0xbf,handle_interrupt_request_bf, 0);
    set_idt_entry(0xc0,handle_interrupt_request_c0, 0);
    set_idt_entry(0xc1,handle_interrupt_request_c1, 0);
    set_idt_entry(0xc2,handle_interrupt_request_c2, 0);
    set_idt_entry(0xc3,handle_interrupt_request_c3, 0);
    set_idt_entry(0xc4,handle_interrupt_request_c4, 0);
    set_idt_entry(0xc5,handle_interrupt_request_c5, 0);
    set_idt_entry(0xc6,handle_interrupt_request_c6, 0);
    set_idt_entry(0xc7,handle_interrupt_request_c7, 0);
    set_idt_entry(0xc8,handle_interrupt_request_c8, 0);
    set_idt_entry(0xc9,handle_interrupt_request_c9, 0);
    set_idt_entry(0xca,handle_interrupt_request_ca, 0);
    set_idt_entry(0xcb,handle_interrupt_request_cb, 0);
    set_idt_entry(0xcc,handle_interrupt_request_cc, 0);
    set_idt_entry(0xcd,handle_interrupt_request_cd, 0);
    set_idt_entry(0xce,handle_interrupt_request_ce, 0);
    set_idt_entry(0xcf,handle_interrupt_request_cf, 0);
    set_idt_entry(0xd0,handle_interrupt_request_d0, 0);
    set_idt_entry(0xd1,handle_interrupt_request_d1, 0);
    set_idt_entry(0xd2,handle_interrupt_request_d2, 0);
    set_idt_entry(0xd3,handle_interrupt_request_d3, 0);
    set_idt_entry(0xd4,handle_interrupt_request_d4, 0);
    set_idt_entry(0xd5,handle_interrupt_request_d5, 0);
    set_idt_entry(0xd6,handle_interrupt_request_d6, 0);
    set_idt_entry(0xd7,handle_interrupt_request_d7, 0);
    set_idt_entry(0xd8,handle_interrupt_request_d8, 0);
    set_idt_entry(0xd9,handle_interrupt_request_d9, 0);
    set_idt_entry(0xda,handle_interrupt_request_da, 0);
    set_idt_entry(0xdb,handle_interrupt_request_db, 0);
    set_idt_entry(0xdc,handle_interrupt_request_dc, 0);
    set_idt_entry(0xdd,handle_interrupt_request_dd, 0);
    set_idt_entry(0xde,handle_interrupt_request_de, 0);
    set_idt_entry(0xdf,handle_interrupt_request_df, 0);
    set_idt_entry(0xe0,handle_interrupt_request_e0, 0);
    set_idt_entry(0xe1,handle_interrupt_request_e1, 0);
    set_idt_entry(0xe2,handle_interrupt_request_e2, 0);
    set_idt_entry(0xe3,handle_interrupt_request_e3, 0);
    set_idt_entry(0xe4,handle_interrupt_request_e4, 0);
    set_idt_entry(0xe5,handle_interrupt_request_e5, 0);
    set_idt_entry(0xe6,handle_interrupt_request_e6, 0);
    set_idt_entry(0xe7,handle_interrupt_request_e7, 0);
    set_idt_entry(0xe8,handle_interrupt_request_e8, 0);
    set_idt_entry(0xe9,handle_interrupt_request_e9, 0);
    set_idt_entry(0xea,handle_interrupt_request_ea, 0);
    set_idt_entry(0xeb,handle_interrupt_request_eb, 0);
    set_idt_entry(0xec,handle_interrupt_request_ec, 0);
    set_idt_entry(0xed,handle_interrupt_request_ed, 0);
    set_idt_entry(0xee,handle_interrupt_request_ee, 0);
    set_idt_entry(0xef,handle_interrupt_request_ef, 0);
    set_idt_entry(0xf0,handle_interrupt_request_f0, 0);
    set_idt_entry(0xf1,handle_interrupt_request_f1, 0);
    set_idt_entry(0xf2,handle_interrupt_request_f2, 0);
    set_idt_entry(0xf3,handle_interrupt_request_f3, 0);
    set_idt_entry(0xf4,handle_interrupt_request_f4, 0);
    set_idt_entry(0xf5,handle_interrupt_request_f5, 0);
    set_idt_entry(0xf6,handle_interrupt_request_f6, 0);
    set_idt_entry(0xf7,handle_interrupt_request_f7, 0);
    set_idt_entry(0xf8,handle_interrupt_request_f8, 0);
    set_idt_entry(0xf9,handle_interrupt_request_f9, 0);
    set_idt_entry(0xfa,handle_interrupt_request_fa, 0);
    set_idt_entry(0xfb,handle_interrupt_request_fb, 0);
    set_idt_entry(0xfc,handle_interrupt_request_fc, 0);
    set_idt_entry(0xfd,handle_interrupt_request_fd, 0);
    set_idt_entry(0xfe,handle_interrupt_request_fe, 0);
    set_idt_entry(0xff,handle_interrupt_request_ff, 0);

    write_idtr(&idt);
}

