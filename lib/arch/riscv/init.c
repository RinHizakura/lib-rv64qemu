#include "arch/riscv/device.h"
#include "arch/riscv/machine.h"

#include <stddef.h>
#include <stdlib.h>

int main(int argc, char **argv);

void lib_main()
{
    machine_setup();

    char *argv[] = {"dummy", NULL};
    int ret = main(1, argv);
    console_dev->putchar(ret);
    exit(ret);
    while (1)
        ;
}
