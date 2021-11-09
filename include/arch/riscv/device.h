#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

typedef struct console_device {
    void (*init)(uint64_t, uint16_t);
    int (*getchar)();
    int (*putchar)(int);
} console_device_t;

typedef struct poweroff_device {
    void (*init)(uint64_t);
    void (*poweroff)(int);
} poweroff_device_t;

extern console_device_t *console_dev;
extern console_device_t console_uart16550;
extern poweroff_device_t *poweroff_dev;
extern poweroff_device_t poweroff_sifive_test;

void register_console(console_device_t *dev,
                      uint64_t base_addr,
                      uint16_t divisor);
void register_poweroff(poweroff_device_t *dev, uint64_t base_addr);
#endif
