#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/* Warning: The vsprintf function can be dangerous because it can potentially
 * output more characters than can fit in the allocation size of the string s!
 */
int vsprintf(char *s, const char *format, va_list arg)
{
    size_t pos = 0;
    bool longarg = false;

    for (; *format; format++) {
        if (*format == '%') {
        format:
            format++;
            switch (*format) {
            case 'l': {
                longarg = true;
                goto format;
            } break;
            case 'd': {
                long num = longarg ? va_arg(arg, long) : va_arg(arg, int);
                if (num < 0) {
                    num *= -1;
                    s[pos] = '-';
                }
                pos++;

                int digits = 1;
                for (long nn = num; nn /= 10; digits++)
                    ;
                for (int i = digits - 1; i >= 0; i--) {
                    s[pos + i] = '0' + (num % 10);
                    num /= 10;
                }
                pos += digits;
                longarg = false;
            } break;
            case 'x': {
                int digits;
                long num;
                if (!longarg) {
                    num = va_arg(arg, int);
                    digits =
                        (((sizeof(int) * 8) - __builtin_clz(num) - 1) / 4) + 1;
                } else {
                    num = va_arg(arg, long);
                    digits =
                        (((sizeof(long) * 8) - __builtin_clzl(num) - 1) / 4) +
                        1;
                }
                for (int i = digits - 1; i >= 0; i--) {
                    int tmp = num & 0xf;
                    s[pos + i] = tmp < 10 ? '0' + tmp : 'a' + tmp - 10;
                    num >>= 4;
                }
                pos += digits;
                longarg = false;
            } break;
            case 'c': {
                s[pos++] = (char) va_arg(arg, int);
            } break;
            case 's': {
                const char *s2 = va_arg(arg, const char *);
                while (*s2) {
                    s[pos++] = *s2;
                    s2++;
                }
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
