#ifndef __UTIL_DEF_H__
#define __UTIL_DEF_H__

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

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

#define LIKELY(x) __builtin_expect((x),1)
#define UNLIKELY(x) __builtin_expect((x),0)

#endif //__UTIL_DEF_H__
