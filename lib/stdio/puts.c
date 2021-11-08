#include <stdio.h>

int puts(const char *s)
{
    while (*s)
        putchar(*s++);
    putchar('\n');
    return 0;  // simply return a non-negative value 0
}
