#ifndef _RTC_H_
#define _RTC_H_

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t week;
    uint8_t month;
    uint16_t year;
} rtc_counter_value_t;

OS_EXT FlagStatus F_500MS;
OS_EXT FlagStatus F_500MS_1;
OS_EXT FlagStatus F_SET_COL;
OS_EXT FlagStatus F_1SEC;
OS_EXT FlagStatus F_1MIN;
OS_EXT FlagStatus Time_format; //=0,24HR. =1,12HR.
OS_EXT FlagStatus F_DM_MD;     //=0,DM. =1,MD.

OS_EXT uint8_t MinCtr;

extern rtc_counter_value_t TIME;

typedef enum {
    _24HR_,
    _12HR_,
} Flag_HR;
OS_EXT Flag_HR F_HR; //= 1 is 12HR,= 0 is 24HR.

typedef enum {
    _AM_,
    _PM_,
} Flag_AM;
OS_EXT Flag_AM F_AM_PM;

void RTC_Init_Software();
void TimeInit();
uint8_t TimeFormat(uint8_t hour);
void Time_Deal();
void Date_Deal();
uint8_t Date_Day(uint16_t Year, uint8_t Month);
void Week_Deal(uint16_t Year, uint8_t Month, uint8_t Day);

#if 0
void MIN_INC (void);
void MIN_DEC (void);
void HOUR_INC (void);
void HOUR_DEC (void);
void DAY_INC (void);
void DAY_DEC (void);
void MONTH_INC (void);
void MONTH_DEC (void);
void YEAR_INC (void);
void YEAR_DEC (void);
#endif

#endif
