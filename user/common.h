#ifndef COMMON_H
#define COMMON_H

//Data Type const
#ifdef OS_GLOBALS
#define OS_EXT extern
#else
#define OS_EXT
#endif

#define NTC         1
#define _TH_        0
#define _OLED_6448_ 1
#define MY_PRINTF   0

/* Includes system -----------------------------------------------------------*/
#include <math.h>
//#include <intrins.h>
//#include <stdio.h>
#include <string.h>

/* Includes User -------------------------------------------------------------*/
#include "stm8l15x_conf.h"

#include "type_define.h"
//#include "delay.h"
#include "main.h"
#include "gp_sub.h"
#include "uart.h"
#include "initialization.h"
//#include "stm8l_low_power.h"
#include "adc_func.h"
#include "key_process.h"
#include "port_define.h"

#include "th_test.h"
#include "rtc.h"
#include "ntc.h"
#include "oled_6448.h"
#include "my_printf.h"

#endif
