#ifndef INCLUDES_H
#define INCLUDES_H

//Data Type const
#ifdef OS_GLOBALS
#define OS_EXT extern
#else
#define OS_EXT
#endif

#define NTC               1
#define TH                0
#define SUPPORT_OLED_6448 1
#define SUPPORT_MY_PRINTF 0

#include "stm8l15x_conf.h"
#include "stm8l15x_it.h"

#include "type_define.h"
#include "main.h"
#include "common.h"
#include "gp_sub.h"
#include "uart.h"
#include "initialization.h"
#include "adc_func.h"
#include "key_process.h"
#include "port_define.h"

#include "th_test.h"
#include "rtc.h"
#include "ntc.h"
#include "oled_6448.h"
#include "my_printf.h"

#endif
