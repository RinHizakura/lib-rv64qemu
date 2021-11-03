#include "arch/riscv/device.h"

/* Assume:
 * - the global clock rate is 1.8432 MHz
 * - the output freq of the Baudout is equal to the 16X of transmission baud
 * rate
 * - we want 115200 BAUD rate
 *
 * Then the divisor should be: ceil( (1.8432 * 10 ^6) / (16 * 115200) ) = 1.0
 */
#define UART16550_BASE_ADDR 0x10000000
#define UART16550_DIVISOR 1

void machine_setup()
{
    register_console(&console_uart16550, UART16550_BASE_ADDR,
                     UART16550_DIVISOR);
}
