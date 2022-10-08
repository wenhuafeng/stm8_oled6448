

#ifndef COMMON_H
#define COMMON_H

/*----------------------------------------------------------------------------*/
//Data Type const
#ifdef  OS_GLOBALS
#define OS_EXT  extern
#else
#define OS_EXT
#endif

#define _AC_DC_PUMP_            1
#define _DELAY_3S_VENT_         1
#define _TH_                    1
#define _NTC_                   0
#define _OLED_6448_             1
#define _SOFTWARE_RTC_          1

#define _UART_FUNC_             0
#define _SYS_PRINTF_FUNC_       0
#define _MY_PRINTF_FUNC_        0


/* Includes system -----------------------------------------------------------*/
#include <math.h>
//#include <intrins.h>
#include <stdio.h>
#include <string.h>

/* Includes User -------------------------------------------------------------*/
#include "stdio.h"
#include "stm8l15x_conf.h"

#include "type_define.h"
#include "delay.h"
#include "main.h"
#include "gp_sub.h"
#include "initialization.h"
#include "stm8l_low_power.h"
#include "adc_func.h"
#include "key_process.h"

#if (_TH_)
#include "TH_TEST.h"
#endif

#if (_NTC_)
#include "NTC.h"
#endif

#if (_SOFTWARE_RTC_)
#include "RTC.h"
#endif

#if (_OLED_6448_)
#include "OLED_6448.h"
#endif

#if (_UART_FUNC_)
#include "uart.h"
#endif

#if (_MY_PRINTF_FUNC_)
#include "my_printf.h"
#endif

#if (_EEPROM_FUNC_)
#include "EEPROM.h"
#endif

#endif

