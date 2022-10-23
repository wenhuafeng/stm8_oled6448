#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "includes.h"
#endif

struct TimeType TIME;

struct TimeType *RTC_GetTimeAddr(void)
{
    return &TIME;
}

void TimeInit(void)
{
    TIME.year  = 2022;
    TIME.month = 1;
    TIME.day   = 1;
    Week_Deal(TIME.year, TIME.month, TIME.day);
    TIME.hour = 0;
    TIME.min  = 0;
    TIME.sec  = 0;
}

static uint8_t GetMaxDay(uint16_t year, uint8_t month)
{
    uint8_t day;
    uint8_t daysTable[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2) {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
            day = 29;
        } else {
            day = 28;
        }
    } else {
        day = daysTable[month];
    }

    return day;
}

static void CalculateWeek(struct TimeType *time)
{
    int16_t yearTemp = 0;
    int16_t yearHigh;
    int16_t yearLow;
    int8_t monthTemp = 0;
    int8_t wk;

    if (time == NULL) {
        return;
    }

    if (time->month < 3) {
        monthTemp = time->month + 12;
        yearTemp  = time->year - 1;
    } else {
        monthTemp = time->month;
        yearTemp  = time->year;
    }

    yearHigh = yearTemp / 100;
    yearLow  = yearTemp % 100;

    wk = yearLow + (yearLow / 4) + (yearHigh / 4);
    wk = wk - (2 * yearHigh) + (26 * (monthTemp + 1) / 10) + time->day - 1;
    wk = (wk + 140) % 7;

    time->week = wk;
}

bool TIME_Run(void)
{
    struct TimeType *time = &TIME;

    time->sec++;
    if (time->sec < 60) {
        return FALSE;
    }

    time->sec = 0;
    time->min++;
    if (time->min < 60) {
        return FALSE;
    }

    time->min = 0;
    time->hour++;
    if (time->hour < 24) {
        return FALSE;
    }

    time->hour = 0;
    time->day++;
    if (time->day <= GetMaxDay(time->year, time->month)) {
        goto calc_week;
    }

    time->day = 1;
    time->month++;
    if (time->month < 13) {
        goto calc_week;
    }

    time->month = 1;
    time->year++;

calc_week:
    CalculateWeek(time);

    return TRUE;
}
