#ifndef MY_PRINTF_H
#define MY_PRINTF_H

#include "uart.h"

#define __out_putchar putchar

#define MAX_NUMBER_BYTES 10

extern uint8_t my_printf_test(void);
uint8_t printf(const char *fmt, ...);

#endif /* _MY_PRINTF_H */
