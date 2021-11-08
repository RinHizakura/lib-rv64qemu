#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/* Warning: The vsprintf function can be dangerous because it can potentially
 * output more characters than can fit in the allocation size of the string s!
 */
int vsprintf(char *s, const char *format, va_list arg)
{
    size_t pos = 0;
    bool longarg = 0;

    for (; *format; format++) {
        if (*format == '%') {
            format++;
            switch (*format) {
            case 'd': {
                long num = longarg ? va_arg(arg, long) : va_arg(arg, int);
                if (num < 0) {
                    num *= -1;
                    s[pos] = '-';
                }
                pos++;

                long digits = 1;
                for (long nn = num; nn /= 10; digits++)
                    ;
                for (int i = digits - 1; i >= 0; i--) {
                    s[pos + i] = '0' + (num % 10);
                    num /= 10;
                }
                pos += digits;
            } break;
            case 'x': {
                long num = longarg ? va_arg(arg, long) : va_arg(arg, int);
                int long_bits = (longarg ? sizeof(long) : sizeof(int)) * 8;
                long digits = ((long_bits - __builtin_clz(num) - 1) / 4) + 1;
                for (int i = digits - 1; i >= 0; i--) {
                    int tmp = num & 0xf;
                    s[pos + i] = tmp < 10 ? '0' + tmp : 'a' + tmp - 10;
                    num >>= 4;
                }
                pos += digits;
            } break;
            default:
                break;
            }

            continue;
        }
        s[pos++] = *format;
    }
    s[pos] = '\0';
    return pos;
}
