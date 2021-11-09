#include "arch/riscv/device.h"

void exit(int status)
{
    poweroff_dev->poweroff(status);
    while (1)
        ;
}
