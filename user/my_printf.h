#ifndef _MY_PRINTF_H
#define _MY_PRINTF_H

#include "uart.h"
#define __out_putchar putchar

#define MAX_NUMBER_BYTES 10

extern u8 my_printf_test(void);
u8 printf(const char *fmt, ...);

#endif /* _MY_PRINTF_H */
