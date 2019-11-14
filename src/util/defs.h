#ifndef TOMATKERNEL_DEFS_H
#define TOMATKERNEL_DEFS_H

#define POKE(type, addr) (*((volatile type*)(addr)))
#define POKE8(addr) POKE(uint8_t, addr)
#define POKE16(addr) POKE(uint16_t, addr)
#define POKE32(addr) POKE(uint32_t, addr)
#define POKE64(addr) POKE(uint64_t, addr)


#define RELAXED_POKE(type, addr) (*((type*)(addr)))
#define RELAXED_POKE8(addr) RELAXED_POKE(uint8_t, addr)
#define RELAXED_POKE16(addr) RELAXED_POKE(uint16_t, addr)
#define RELAXED_POKE32(addr) RELAXED_POKE(uint32_t, addr)
#define RELAXED_POKE64(addr) RELAXED_POKE(uint64_t, addr)


#define ALIGN_DOWN(n, a) (((uint64_t)n) & ~((a) - 1ul))
#define ALIGN_UP(n, a) ALIGN_DOWN(((uint64_t)n) + (a) - 1ul, (a))
#define ALIGN_PAGE_DOWN(n) ALIGN_DOWN(n, PAGE_SIZE)
#define ALIGN_PAGE_UP(n) ALIGN_UP(n, PAGE_SIZE)

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

#endif //TOMATKERNEL_DEFS_H
