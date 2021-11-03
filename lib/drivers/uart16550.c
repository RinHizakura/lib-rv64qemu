#include "arch/riscv/device.h"

#define UART_RHR 0
#define UART_THR 0
#define UART_LSB 0
#define UART_IER 1
#define UART_MSB 1
#define UART_FCR 2
#define UART_LCR 3
#define UART_LSR 5

static volatile uint8_t *uart;

static void uart16550_init(uint64_t base_addr, uint16_t divisor)
{
    uart = (uint8_t *) base_addr;

    // set word length to 8 bits
    uart[UART_LCR] = 0x3;
    // enable the transmit and receive FIFO
    uart[UART_FCR] = 0x1;
    // enable the receiver ready interrupt
    uart[UART_IER] = 0x1;

    uint8_t divisor_least = divisor & 0xff;
    uint8_t divisor_most = divisor >> 8;

    // enable the divisor latch
    uint8_t lcr_value = uart[UART_LCR];
    uart[UART_LCR] = lcr_value | (1 << 7);

    // set the Divisor Latch when Enabled
    uart[UART_LSB] = divisor_least;
    uart[UART_MSB] = divisor_most;

    // restore LCR to access original register
    uart[UART_LCR] = lcr_value;
}

static int uart16550_getchar()
{
    // TODO
    return 'a';
}

static int uart16550_putchar(int ch)
{
    while (!(uart[UART_LSR] & 0x20))
        ;
    uart[UART_THR] = ch;
    return 0;
}

// this structure define the console operation of uart 16550
console_device_t console_uart16550 = {
    .init = uart16550_init,
    .getchar = uart16550_getchar,
    .putchar = uart16550_putchar,
};
