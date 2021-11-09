#include "arch/riscv/device.h"
// Ref:
// https://github.com/qemu/qemu/blob/master/include/hw/misc/sifive_test.h#L39
#define SIFIVE_FINISHER_PASS 0x5555
#define SIFIVE_FINISHER_FAIL 0x3333
static volatile uint32_t *test;

static void sifive_test_init(uint64_t base_addr)
{
    test = (uint32_t *) base_addr;
}

static void sifive_test_poweroff(int status)
{
    *test = status ? SIFIVE_FINISHER_FAIL : SIFIVE_FINISHER_PASS;
    while (1)
        ;
}

poweroff_device_t poweroff_sifive_test = {.init = sifive_test_init,
                                          .poweroff = sifive_test_poweroff};
