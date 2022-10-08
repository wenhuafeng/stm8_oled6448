#ifndef _USART_H_
#define _USART_H_

#define BAUDRATE 115200
#define SIZE     128

typedef struct uart_rxbuf_s {
    uint8_t buf[SIZE];
    uint32_t len;
} uart_rxbuf_t;

extern uart_rxbuf_t g_uart_rxbuf;

extern void uart_init(void);
extern void uart_send(char *buf, int len);
extern int uart_getchar(void);

#endif
