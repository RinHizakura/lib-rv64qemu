#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

typedef struct console_device {
    void (*init)(uint64_t, uint16_t);
    int (*getchar)();
    int (*putchar)(int);
} console_device_t;

extern console_device_t *console_dev;
extern console_device_t console_uart16550;

void register_console(console_device_t *dev,
                      uint64_t base_addr,
                      uint16_t divisor);

#endif
