#include "arch/riscv/device.h"

console_device_t *console_dev;
poweroff_device_t *poweroff_dev;

void register_console(console_device_t *dev,
                      uint64_t base_addr,
                      uint16_t divisor)
{
    console_dev = dev;
    if (dev->init) {
        dev->init(base_addr, divisor);
    }
}

void register_poweroff(poweroff_device_t *dev, uint64_t base_addr)
{
    poweroff_dev = dev;
    if (dev->init) {
        dev->init(base_addr);
    }
}
