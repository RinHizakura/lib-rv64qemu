#ifndef QEMU_STDIO_H
#define QEMU_STDIO_H

#include <stdarg.h>
#include <stddef.h>

int putchar(int ch);
int puts(const char *s);
int printf(const char *format, ...);
int vsprintf(char *s, const char *format, va_list arg);

#endif
