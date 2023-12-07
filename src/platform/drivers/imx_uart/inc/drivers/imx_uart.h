#ifndef IMX_UART_H
#define IMX_UART_H

#include <stdint.h>

struct imx_uart {
    uint32_t rxd; /* 0x0 */
    uint32_t reserved1[0xf]; /* (0x40 - 0x4)  / 4 */
    uint32_t txd; /* 0x40*/
    uint32_t reserved2[0xf]; /* (0x80 - 0x44) / 4 */
    uint32_t cr1; /* 0x80 */
    uint32_t cr2; /* 0x84 */
    uint32_t cr3; /* 0x88 */
    uint32_t cr4; /* 0x8c */
    uint32_t fcr; /* 0x90 */
    uint32_t stat1; /* 0x94 */
    uint32_t stat2; /* 0x98 */
    uint32_t esc; /* 0x9c */
    uint32_t tim; /* 0xa0 */
    uint32_t bir; /* 0xa4 */
    uint32_t bmr; /* 0xa8 */
    uint32_t brc; /* 0xac */
    uint32_t onems; /* 0xb0 */
    uint32_t ts; /* 0xb4 */
};

typedef struct imx_uart bao_uart_t;

void uart_enable(volatile struct imx_uart *uart);
void uart_init(volatile struct imx_uart *uart);
void uart_puts(volatile struct imx_uart * uart, const char* str);
void uart_putc(volatile struct imx_uart * uart, char str);

#endif /* IMX_UART_H */
