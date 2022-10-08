
#ifndef _LED_CONTROL_H_
#define _LED_CONTROL_H_


#define LED_PWM_GEAR_LOW   LED1
#define LED_PWM_GEAR_MID   LED2
#define LED_PWM_GEAR_HIGH  LED3

#define LED_BAT_IND_LOW    LED6
#define LED_BAT_IND_MID    LED4
#define LED_BAT_IND_HIGH   LED5

//-----------------------------------------------------------

enum {
  _LED_BI_OFF_,
  _LED_CHARGE_,         //Battery charge indicator
  _LED_FLASH_,          //Alarm wanning
  _LED_BAT_IND_THREE_,  //Battery indicator three
  _LED_BAT_IND_TWO_,    //Battery indicator two
  _LED_BAT_IND_ONE_,    //Battery indicator one
  _LED_BAT_IND_EMPTY_,  //Battery indicator empty
};
OS_EXT u8 LED_ChargeStatic;

enum {
  _LED_PWM_OFF_,
  _LED_LOW_,
  _LED_MID_,
  _LED_HIGH_,
};
OS_EXT u8 LED_PwmGear;

//enum {
//  _SWITCH_OFF_,
//  _SWITCH_LOW_,
//  _SWITCH_MID_,
//  _SWITCH_HIGH_,
//};

enum {
  _WORK_ERROR_,
  _WORK_OFF_,
  _WORK_LOW_,
  _WORK_MID_,
  _WORK_HIGH_,
};
//OS_EXT u8 Switch;

#define _LED_BAT_IND_TIME_               (10*2+1)
OS_EXT u8 LED_BatteryIndicatorCtr;

//-----------------------------------------------------------

void LED_ControlManage(void);
void LED_AllOnOff(FlagStatus F_tmp);
void LED_PwmGearSet(u8 gear);
void LED_ChargeStaticSet(u8 sta);

void LED_SetBatVolInd(void);
void LED_SetBatVolInd_10S(u8 temp);
void LED_BatVolIndCtrDec(void);

#endif