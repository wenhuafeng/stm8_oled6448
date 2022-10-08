#ifndef USART_H
#define USART_H

extern void uart_init(void);
extern void uart_send(char *buf, int len);
extern int uart_getchar(void);
extern void uart_rx_data(void);

#endif
