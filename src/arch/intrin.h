#ifndef __ARCH_INTRIN_H__
#define __ARCH_INTRIN_H__

#include <stdint.h>
#include <assert.h>

void __outbyte(uint16_t port, uint8_t data);
void __outword(uint16_t port, uint16_t data);
void __outdword(uint16_t port, uint32_t data);

uint8_t __inbyte(uint16_t port);
uint16_t __inword(uint16_t port);
uint32_t __indword(uint16_t port);

uint64_t __readcr8(void);
void __writecr8(uint64_t Data);

typedef union {
    struct {
        uint32_t  VME:1;          ///< Virtual-8086 Mode Extensions.
        uint32_t  PVI:1;          ///< Protected-Mode Virtual Interrupts.
        uint32_t  TSD:1;          ///< Time Stamp Disable.
        uint32_t  DE:1;           ///< Debugging Extensions.
        uint32_t  PSE:1;          ///< Page Size Extensions.
        uint32_t  PAE:1;          ///< Physical Address Extension.
        uint32_t  MCE:1;          ///< Machine Check Enable.
        uint32_t  PGE:1;          ///< Page Global Enable.
        uint32_t  PCE:1;          ///< Performance Monitoring Counter
                                  ///< Enable.
        uint32_t  OSFXSR:1;       ///< Operating System Support for
                                  ///< FXSAVE and FXRSTOR instructions
        uint32_t  OSXMMEXCPT:1;   ///< Operating System Support for
                                  ///< Unmasked SIMD Floating Point
                                  ///< Exceptions.
        uint32_t  UMIP:1;         ///< User-Mode Instruction Prevention.
        uint32_t  LA57:1;         ///< Linear Address 57bit.
        uint32_t  VMXE:1;         ///< VMX Enable.
        uint32_t  SMXE:1;         ///< SMX Enable.
        uint32_t  _reserved3:1;   ///< Reserved.
        uint32_t  FSGSBASE:1;     ///< FSGSBASE Enable.
        uint32_t  PCIDE:1;        ///< PCID Enable.
        uint32_t  OSXSAVE:1;      ///< XSAVE and Processor Extended States Enable.
        uint32_t  _reserved4:1;   ///< Reserved.
        uint32_t  SMEP:1;         ///< SMEP Enable.
        uint32_t  SMAP:1;         ///< SMAP Enable.
        uint32_t  PKE:1;          ///< Protection-Key Enable.
        uint32_t  _reserved5:9;   ///< Reserved.
    };
    uint64_t raw;
} IA32_CR4;
static_assert(sizeof(IA32_CR4) == sizeof(uint64_t));

IA32_CR4 __readcr4(void);
void __writecr4(IA32_CR4 Data);

uint64_t __readcr3(void);
void __writecr3(uint64_t Data);

uint64_t __readcr2(void);
void __writecr2(uint64_t Data);

typedef union IA32_CR0 {
    struct {
        uint32_t  PE:1;           ///< Protection Enable.
        uint32_t  MP:1;           ///< Monitor Coprocessor.
        uint32_t  EM:1;           ///< Emulation.
        uint32_t  TS:1;           ///< Task Switched.
        uint32_t  ET:1;           ///< Extension Type.
        uint32_t  NE:1;           ///< Numeric Error.
        uint32_t  _reserved0:10;  ///< Reserved.
        uint32_t  WP:1;           ///< Write Protect.
        uint32_t  _reserved1:1;   ///< Reserved.
        uint32_t  AM:1;           ///< Alignment Mask.
        uint32_t  _reserved2:10;  ///< Reserved.
        uint32_t  NW:1;           ///< Mot Write-through.
        uint32_t  CD:1;           ///< Cache Disable.
        uint32_t  PG:1;           ///< Paging.
    };
    uint64_t raw;
} IA32_CR0;
static_assert(sizeof(IA32_CR0) == sizeof(uint64_t));

IA32_CR0 __readcr0(void);
void __writecr0(IA32_CR0 Data);

uint64_t __readmsr(uint32_t msr);
void __writemsr(uint32_t msr, uint64_t Value);

void __cpuid(int __info[4], int __level);
void __cpuidex(int __info[4], int __level, int __ecx);

void __invlpg(uintptr_t a);

void __halt(void);
void __nop(void);

void __ltr(uint16_t seg);

void __swapgs(void);

///
/// Byte packed structure for EFLAGS/RFLAGS.
/// 32-bits on IA-32.
/// 64-bits on x64.  The upper 32-bits on x64 are reserved.
///
typedef union {
    struct {
        uint32_t  CF:1;           ///< Carry Flag.
        uint32_t  always_one:1;   ///< Reserved.
        uint32_t  PF:1;           ///< Parity Flag.
        uint32_t  _reserved_1:1;   ///< Reserved.
        uint32_t  AF:1;           ///< Auxiliary Carry Flag.
        uint32_t  _reserved_2:1;   ///< Reserved.
        uint32_t  ZF:1;           ///< Zero Flag.
        uint32_t  SF:1;           ///< Sign Flag.
        uint32_t  TF:1;           ///< Trap Flag.
        uint32_t  IF:1;           ///< Interrupt Enable Flag.
        uint32_t  DF:1;           ///< Direction Flag.
        uint32_t  OF:1;           ///< Overflow Flag.
        uint32_t  IOPL:2;         ///< I/O Privilege Level.
        uint32_t  NT:1;           ///< Nested Task.
        uint32_t  _reserved_3:1;   ///< Reserved.
        uint32_t  RF:1;           ///< Resume Flag.
        uint32_t  VM:1;           ///< Virtual 8086 Mode.
        uint32_t  AC:1;           ///< Alignment Check.
        uint32_t  VIF:1;          ///< Virtual Interrupt Flag.
        uint32_t  VIP:1;          ///< Virtual Interrupt Pending.
        uint32_t  ID:1;           ///< ID Flag.
        uint32_t  _reserved_4:10;  ///< Reserved.
    };
    uint64_t raw;
} IA32_RFLAGS;
static_assert(sizeof(IA32_RFLAGS) == sizeof(uint64_t));

unsigned char _BitScanReverse(uint32_t* Index, uint32_t Mask);
unsigned char _BitScanReverse64(uint32_t* Index, uint64_t Mask);

#endif //__ARCH_INTRIN_H__
