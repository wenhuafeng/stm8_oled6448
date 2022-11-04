#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "includes.h"
#endif

#if (SUPPORT_MY_PRINTF)

typedef char *va_list;
#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))

#define va_start(ap, v) (ap = (va_list)&v + _INTSIZEOF(v))
//#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_arg(ap, t) (*(t *)(ap = ap + _INTSIZEOF(t), ap - _INTSIZEOF(t)))
#define va_end(ap)    (ap = (va_list)0)

const uint8_t hex_tab[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

uint8_t getchar(void)
{
    uint8_t c = 0;

    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    c = USART_ReceiveData8(USART1);

    return (c);
}

uint8_t putchar(uint8_t c)
{
    USART_SendData8(USART1, c);
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return (c);
}

void puts(uint8_t *s)
{
    while (*s) {
        putchar(*s);
        s++;
    }
}

static uint8_t outc(uint8_t c)
{
    __out_putchar(c);

    return 0;
}

static uint8_t outs(uint8_t *s)
{
    while (*s != '\0') {
        __out_putchar(*s++);
    }

    return 0;
}

static uint8_t out_num(int32_t n, uint8_t base, char lead, uint8_t maxwidth)
{
    uint8_t m = 0;
    uint8_t buf[MAX_NUMBER_BYTES];
    uint8_t *s    = buf + sizeof(buf);
    uint8_t count = 0;
    uint8_t i     = 0;

    *--s = '\0';

    if (n < 0) {
        m = -n;
    } else {
        m = n;
    }

    do {
        *--s = hex_tab[m % base];
        count++;
    } while ((m /= base) != 0);

    if (maxwidth && count < maxwidth) {
        for (i = maxwidth - count; i; i--) {
            *--s = lead;
        }
    }

    if (n < 0) {
        *--s = '-';
    }

    return outs(s);
}

/* reference :   int vprintf(const char *format, va_list ap); */
static uint8_t my_vprintf(const char *fmt, va_list ap)
{
    uint8_t lead     = ' ';
    uint8_t maxwidth = 0;

    for (; *fmt != '\0'; fmt++) {
        if (*fmt != '%') {
            outc(*fmt);
            continue;
        }

        // format : %08d, %8d,%d,%u,%x,%f,%c,%s
        fmt++;
        if (*fmt == '0') {
            lead = '0';
            fmt++;
        }

        lead     = ' ';
        maxwidth = 0;

        while (*fmt >= '0' && *fmt <= '9') {
            maxwidth *= 10;
            maxwidth += (*fmt - '0');
            fmt++;
        }

        switch (*fmt) {
            case 'd':
                out_num(va_arg(ap, int32_t), 10, lead, maxwidth);
                break;
            case 'o':
                out_num(va_arg(ap, uint32_t), 8, lead, maxwidth);
                break;
            case 'u':
                out_num(va_arg(ap, uint32_t), 10, lead, maxwidth);
                break;
            case 'x':
                out_num(va_arg(ap, uint32_t), 16, lead, maxwidth);
                break;
            case 'c':
                outc(va_arg(ap, uint8_t));
                break;
            case 's':
                outs(va_arg(ap, uint8_t *));
                break;
            default:
                outc(*fmt);
                break;
        }
    }

    return 0;
}

// reference :  int printf(const char *format, ...);
uint8_t printf(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    my_vprintf(fmt, ap);
    va_end(ap);

    return 0;
}

uint8_t printf_test(void)
{
    printf("This is www.100ask.org my_printf test\r\n");
    printf("test char =%c, %c\r\n", 'A', 'a');
    printf("test decimal number =%d\r\n", 123456);
    printf("test decimal number =%d\r\n", -123456);
    printf("test hex number =0x%x\r\n", 0x55aa55aa);
    printf("test string =%s\r\n", "www.100ask.org");
    printf("num=%08d\r\n", 12345);
    printf("num=%8d\r\n", 12345);
    printf("num=0x%08x\r\n", 0x12345);
    printf("num=0x%8x\r\n", 0x12345);
    printf("num=0x%02x\r\n", 0x1);
    printf("num=0x%2x\r\n", 0x1);

    printf("num=%05d\r\n", 0x1);
    printf("num=%5d\r\n", 0x1);

    return 0;
}

#else

//#ifdef _RAISONANCE_
//#define PUTCHAR_PROTOTYPE int putchar(char c)
//#define GETCHAR_PROTOTYPE int getchar(void)
//#elif defined(_COSMIC_)
//#define PUTCHAR_PROTOTYPE char putchar(char c)
//#define GETCHAR_PROTOTYPE char getchar(void)
//#else /* _IAR_ */
//#define PUTCHAR_PROTOTYPE int putchar(int c)
//#define GETCHAR_PROTOTYPE int getchar(void)
//#endif /* _RAISONANCE_ */
//
//PUTCHAR_PROTOTYPE
//{
//    /* Write a character to the USART */
//    USART_SendData8(USART1, c);
//    /* Loop until the end of transmission */
//    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//
//    return (c);
//}

uint8_t printf_test(void)
{
    return 0;
}

#endif
