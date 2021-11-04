#include "arch/riscv/device.h"

int putchar(int ch)
{
    return console_dev->putchar(ch);
}

