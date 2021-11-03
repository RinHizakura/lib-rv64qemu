#include "arch/riscv/device.h"
#include "arch/riscv/machine.h"

void lib_main()
{
    machine_setup();
    console_dev->putchar('A');
    console_dev->putchar('m');
    console_dev->putchar('i');
    console_dev->putchar('t');
    console_dev->putchar('a');
    // exit(main(1,{"dummy", NULL}));
    while (1)
        ;
}
