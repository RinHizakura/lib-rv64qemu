#include "arch/riscv/device.h"

void exit(int status)
{
    console_dev->putchar(status);
    while (1)
        ;
}
