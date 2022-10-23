#ifndef RTC_H
#define RTC_H

struct TimeType {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t week;
    uint8_t month;
    uint16_t year;
};

struct TimeType *RTC_GetTimeAddr(void);
void RTC_Init_Software();
void TimeInit();
uint8_t TimeFormat(uint8_t hour);
bool TIME_Run();
void Date_Deal();
uint8_t Date_Day(uint16_t Year, uint8_t Month);
void Week_Deal(uint16_t Year, uint8_t Month, uint8_t Day);

#endif
