#include <stdarg.h>
#include <stddef.h>

/* Warning: The vsprintf function can be dangerous because it can potentially
 * output more characters than can fit in the allocation size of the string s!
 */
int vsprintf(char *s, const char *format, va_list arg)
{
    size_t pos = 0;

    for (; *format; format++) {
        if (*format == '%') {
            format++;
            switch (*format) {
            case 'd': {
                long int num = va_arg(arg, int);
                if (num < 0) {
                    num *= -1;
                    s[pos] = '-';
                }
                pos++;

                long int digits = 1;
                for (long int nn = num; nn /= 10; digits++)
                    ;
                for (int i = digits - 1; i >= 0; i--) {
                    s[pos + i] = '0' + (num % 10);
                    num /= 10;
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
