#ifndef QEMU_STDINT_H
#define QEMU_STDINT_H

//#if defined __GNUC__

//#define clz(val) __builtin_clz(val)

//#else

#include <stdint.h>

/* FIXME: For int and long type, their size depend on the data models. However,
 * we just simply assume using LP64 data model here.
 *
 * see: https://en.wikipedia.org/wiki/64-bit_computing#64-bit_data_models */
#define clz(x)                 \
    _Generic((x), uint8_t      \
             : clz8, uint16_t  \
             : clz16, uint32_t \
             : clz32, uint64_t \
             : clz64, int      \
             : clz32, long     \
             : clz64)(x)

// FIXME: change to more efficient clz implementation
#define DEFINE_CLZ(bits)                            \
    static inline int clz##bits(uint##bits##_t val) \
    {                                               \
        int n = 0;                                  \
        while (val) {                               \
            val >>= 1;                              \
            n++;                                    \
        }                                           \
        return bits - n;                            \
    }

DEFINE_CLZ(8)
DEFINE_CLZ(16)
DEFINE_CLZ(32)
DEFINE_CLZ(64)

//#endif
#endif /* QEMU_STDINT_H */
