#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

#if (_SOFTWARE_RTC_)

//RTC define
rtc_counter_value_t TIME;

//Init year,month,day,hour,min,sec
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

/*
uint8_t TimeFormat(uint8_t hour)
{
  if (Time_format) { // format = 1 12HR
    if (hour == 0) {
            return (12);
    } else if (hour >12) {
            return (hour - 12);
    } else {
            return (hour);
    }
  } else { // format = 0 24HR
    return (hour);
  }
}*/

//Time running hour,min,sec
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

            //if ((TIME.hour == 2 || TIME.hour == 14) && flag_rdstime_on) {
            //  flag_auto_time_on = 1;
            //}
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

    //return week_data;
}

#if 0

/********************************************************************//**
 * @brief:      MIN++
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void MIN_INC (void)
{
  TIME.sec = 0x00;
  if (++TIME.min >= 60) {
    TIME.min = 0;
    //return 0;
  } else {
    //return 0;
  }
}

/********************************************************************//**
 * @brief:      MIN--
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void MIN_DEC (void)
{
  TIME.sec = 0x00;
  if (--TIME.min == 0xff) {
    TIME.min = 59;
    //return 1;
  } else {
    //return 0;
  }
}

/********************************************************************//**
 * @brief:      HOUR++
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void HOUR_INC (void)
{
  if (++TIME.hour >= 24) {
    TIME.hour = 0;
    //return 1;
  } else {
    //return 0;
  }

}

/********************************************************************//**
 * @brief:      HOUR--
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void HOUR_DEC (void)
{
  if (--TIME.hour == 0xff) {
    TIME.hour = 23;
    //return 1;
  } else {
    //return 0;
  }

}

/********************************************************************//**
 * @brief:      DAY++ and Get max day
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void DAY_INC (void)
{
  if (++TIME.day > Date_Day(TIME.year,TIME.month)) {
    TIME.day = 1;
    //return 1;
  } else {
    //return 0;
  }
}

/********************************************************************//**
 * @brief:      DAY-- and Get max day
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void DAY_DEC (void)
{
  if (--TIME.day == 0) {
    TIME.day = Date_Day(TIME.year,TIME.month);
    //return 1;
  } else {
    //return 0;
  }
}


/********************************************************************//**
 * @brief:      MONTH INC
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void MONTH_INC (void)
{
  //BOOLEAN F_tmp;
  uint8_t MaxDay;

  if (++TIME.month >= 13) {
    TIME.month = 1;
    //F_tmp = 1;
  } else {
    //F_tmp = 0;
  }

  //update Max day
  MaxDay = Date_Day(TIME.year,TIME.month);
  if (TIME.day >= MaxDay) {
    TIME.day = MaxDay;
  }

  //return F_tmp;
}

/********************************************************************//**
 * @brief:      MONTH DEC
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void MONTH_DEC (void)
{
  //BOOLEAN F_tmp;
  uint8_t MaxDay;

  if (--TIME.month == 0) {
    TIME.month = 12;
    //F_tmp = 1;
  } else {
    //F_tmp = 0;
  }

  //update Max day
  MaxDay = Date_Day(TIME.year,TIME.month);
  if (TIME.day >= MaxDay) {
    TIME.day = MaxDay;
  }

  //return F_tmp;
}

/********************************************************************//**
 * @brief:      MONTH INC
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void YEAR_INC (void)
{
  //BOOLEAN F_tmp;
  uint8_t MaxDay;

  if (++TIME.year > 2099) {
    TIME.year = 2000;
    //F_tmp = 1;
  } else {
    //F_tmp = 0;
  }

  //update Max day
  MaxDay = Date_Day(TIME.year,TIME.month);
  if (TIME.day >= MaxDay) {
    TIME.day = MaxDay;
  }

  //return F_tmp;
}

/********************************************************************//**
 * @brief:      MONTH DEC
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void YEAR_DEC (void)
{
  //BOOLEAN F_tmp;
  uint8_t MaxDay;

  if (--TIME.year == 1999) {
    TIME.year = 2099;
    //F_tmp = 1;
  } else {
    //F_tmp = 0;
  }

  //update Max day
  MaxDay = Date_Day(TIME.year,TIME.month);
  if (TIME.day >= MaxDay) {
    TIME.day = MaxDay;
  }

  //return F_tmp;
}

#endif
#endif
