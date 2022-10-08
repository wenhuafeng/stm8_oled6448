#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

#if (_MY_PRINTF_FUNC_)

#define BAUDRATE 115200
#define SIZE     128

typedef struct uart_rxbuf_s {
    uint8_t buf[SIZE];
    uint32_t len;
} uart_rxbuf_t;

uart_rxbuf_t g_uart_rxbuf;

//------------------------------------------------------------------------------
int putchar(int c)
{
    if ('\n' == (char)c) {
        USART_SendData8(USART1, '\r');
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
            ;
    }
    USART_SendData8(USART1, c);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        ;

    return (c);
}

void uart_send(char *buf, int len)
{
    int i;

    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    GPIO_Init(COM_PORT, COM_PIN, GPIO_Mode_Out_PP_High_Fast);
    for (i = 0; i < len; i++) {
        USART1->DR = (unsigned char)buf[i];
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
            ;
    }
    i = USART_ReceiveData8(USART1);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    GPIO_Init(COM_PORT, COM_PIN, GPIO_Mode_In_PU_No_IT);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

int uart_getchar(void)
{
    int c;

    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        ;
    c = USART_ReceiveData8(USART1);

    USART_SendData8(USART1, c);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        ;

    return (c);
}

void uart_rx_data(void)
{
    uint8_t i;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        if (g_uart_rxbuf.len >= sizeof(g_uart_rxbuf.buf)) {
            USART_ReceiveData8(USART1);
            return;
            //goto enable_rx_int;
        }
        i                                    = USART_ReceiveData8(USART1);
        g_uart_rxbuf.buf[g_uart_rxbuf.len++] = i;
        if (i == '5') {
            uart_send("ABC", 3);
        }
    }
}

#else

void uart_rx_data(void) {}

#endif
