

#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

#if (_MY_PRINTF_FUNC_)

u8 getchar(void)
{
    //while (!(UTRSTAT0 & (1<<0)));          //
    //return URXH0;                          //

    u8 i;

    return i;
}

void putchar(u8 c) //
{
    //while (!(UTRSTAT0 & (1<<2)));          //
    //UTXH0 = c;      //(unsigned char)      //

    TI   = 0;
    SBUF = c;
    while (TI == 0)
        ;
}

void puts(u8 *s)
{
    while (*s) {
        putchar(*s);
        s++;
    }
}

//==================================================================================================
typedef char *va_list;
#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))

#define va_start(ap, v) (ap = (va_list)&v + _INTSIZEOF(v))
//#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_arg(ap, t) (*(t *)(ap = ap + _INTSIZEOF(t), ap - _INTSIZEOF(t)))
#define va_end(ap)    (ap = (va_list)0)

//==================================================================================================
code u8 hex_tab[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

static u8 outc(u8 c)
{
    __out_putchar(c);
    return 0;
}

static u8 outs(u8 *s)
{
    while (*s != '\0')
        __out_putchar(*s++);
    return 0;
}

static u8 out_num(u8 n, u8 base, u8 lead, u8 maxwidth)
{
    u8 m = 0;
    idata u8 buf[MAX_NUMBER_BYTES], *s = buf + sizeof(buf);
    u8 count = 0, i = 0;

    *--s = '\0';

    //if (n < 0){
    //  m = -n;
    //}
    //else{
    m = n;
    //}

    do {
        *--s = hex_tab[m % base];
        count++;
    } while ((m /= base) != 0);

    if (maxwidth && count < maxwidth) {
        for (i = maxwidth - count; i; i--)
            *--s = lead;
    }

    if (n < 0)
        *--s = '-';

    return outs(s);
}

/*reference :   int vprintf(const char *format, va_list ap); */
static u8 my_vprintf(u8 *fmt, va_list ap)
{
    u8 lead     = ' ';
    u8 maxwidth = 0;

    for (; *fmt != '\0'; fmt++) {
        if (*fmt != '%') {
            outc(*fmt);
            continue;
        }

        //format : %08d, %8d,%d,%u,%x,%f,%c,%s
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
                out_num(va_arg(ap, u16), 10, lead, maxwidth);
                break;
            //case 'o': out_num(va_arg(ap, unsigned int),  8,lead,maxwidth); break;
            case 'u':
                out_num(va_arg(ap, u16), 10, lead, maxwidth);
                break;
                //case 'x': out_num(va_arg(ap, unsigned int), 16,lead,maxwidth); break;
                //case 'c': outc(va_arg(ap, int   )); break;
                //case 's': outs(va_arg(ap, char *)); break;

            default:
                outc(*fmt);
                break;
        }
    }

    return 0;
}

//reference :  int printf(const char *format, ...);
u8 printf(u8 *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    my_vprintf(fmt, ap);
    va_end(ap);

    return 0;
}

/*
u8 my_printf_test(void)
{
  printf("This is www.100ask.org   my_printf test\n\r") ;
  printf("test char           =%c,%c\n\r", 'A','a') ;
  printf("test decimal number =%d\n\r",    123456) ;
  printf("test decimal number =%d\n\r",    -123456) ;
  printf("test hex     number =0x%x\n\r",  0x55aa55aa) ;
  printf("test string         =%s\n\r",    "www.100ask.org") ;
  printf("num=%08d\n\r",   12345);
  printf("num=%8d\n\r",    12345);
  printf("num=0x%08x\n\r", 0x12345);
  printf("num=0x%8x\n\r",  0x12345);
  printf("num=0x%02x\n\r", 0x1);
  printf("num=0x%2x\n\r",  0x1);

  printf("num=%05d\n\r", 0x1);
  printf("num=%5d\n\r",  0x1);

  return 0;
}*/

#endif
