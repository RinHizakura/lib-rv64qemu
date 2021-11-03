#include "arch/riscv/device.h"

console_device_t *console_dev;

void register_console(console_device_t *dev,
                      uint64_t base_addr,
                      uint16_t divisor)
{
    console_dev = dev;
    if (dev->init) {
        dev->init(base_addr, divisor);
    }
}
