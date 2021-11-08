#include <stdarg.h>
#include <stdio.h>

int printf(const char *format, ...)
{
    /* warning: if the actual format string is larger than 256 characters,
     * we'll meet the buffer overflow problem */

    char buf[256];
    va_list arg;
    va_start(arg, format);
    int len = vsprintf(buf, format, arg);
    va_end(arg);

    for (int i = 0; i < len; i++)
        putchar(buf[i]);
    return len;
}
