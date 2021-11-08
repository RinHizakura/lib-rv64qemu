/* FIXME:
 * 1. For int and long type, their size depend on the data models. However,
 * we just simply assume using LP64 data model here. Could this failed for some
 * scenario? See:
 * https://en.wikipedia.org/wiki/64-bit_computing#64-bit_data_models.
 *
 * 2. We should change to more efficient clz implementation */
int __clzsi2(int val)
{
    int n = 0;
    while (val) {
        val >>= 1;
        n++;
    }
    return 32 - n;
}

int __clzdi2(long val)
{
    int n = 0;
    while (val) {
        val >>= 1;
        n++;
    }
    return 64 - n;
}
