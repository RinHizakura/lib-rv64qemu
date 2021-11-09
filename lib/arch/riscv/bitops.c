#include <stdint.h>
/* FIXME:
 * 1. For int and long type, their size depend on the data models. However,
 * we just simply assume using LP64 data model here. Could this failed for some
 * scenario? See:
 * https://en.wikipedia.org/wiki/64-bit_computing#64-bit_data_models.
 *
 * 2. We should change to more efficient clz implementation */
int __clzsi2(int val)
{
    // convert to unsigned type for bitwise shift operation
    uint32_t tmp = (uint32_t) val;

    int n = 0;
    while (tmp) {
        tmp >>= 1;
        n++;
    }
    return 32 - n;
}

int __clzdi2(long long val)
{
    if (val >> 32) {
        return __clzsi2(val >> 32);
    } else {
        return __clzsi2(val) + 32;
    }
}
