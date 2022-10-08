#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

rtc_counter_value_t TIME;

void TimeInit(void)
{
    TIME.year  = 2018;
    TIME.month = 1;
    TIME.day   = 1;
    Week_Deal(TIME.year, TIME.month, TIME.day);
    TIME.hour = 0;
    TIME.min  = 0;
    TIME.sec  = 0;
}

void Time_Deal(void)
{
    TIME.sec++;
    if (TIME.sec == 60) {
        F_1MIN   = SET;
        TIME.sec = 0;
        TIME.min++;
        if (TIME.min == 60) {
            TIME.min = 0;
            TIME.hour++;
            if (TIME.hour > 23) {
                TIME.hour = 0;
                TIME.day++;
                if (TIME.day > Date_Day(TIME.year, TIME.month)) {
                    TIME.day = 1;
                    TIME.month++;
                    if (TIME.month > 12) {
                        TIME.month = 1;
                        TIME.year++;
                    }
                }
                Week_Deal(TIME.year, TIME.month, TIME.day); //week
            }
        }
    }
}

uint8_t Date_Day(uint16_t Year, uint8_t Month)
{
    uint8_t day_temp;
    uint8_t const_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (Month == 2) {
        if (((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0)) {
            day_temp = 29;
        } else {
            day_temp = 28;
        }
    } else {
        day_temp = const_days[Month];
    }

    return day_temp;
}

void Week_Deal(uint16_t Year, uint8_t Month, uint8_t Day)
{
    int16_t temp_year = 0;
    int8_t temp_cen   = 0;
    int8_t temp_month = 0;
    int8_t week_data;

    if (Month < 3) {
        temp_month = Month + 12;
        temp_year  = Year - 1;
    } else {
        temp_month = Month;
        temp_year  = Year;
    }

    temp_cen  = temp_year / 100; //C;
    temp_year = temp_year % 100; //Y

    week_data = temp_year + temp_year / 4 + temp_cen / 4;
    week_data = week_data - 2 * temp_cen + 26 * (temp_month + 1) / 10 + Day - 1;
    TIME.week = (week_data + 140) % 7;
}
