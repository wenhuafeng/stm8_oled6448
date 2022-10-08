

#ifndef  OS_MASTER_FILE
#define  OS_GLOBALS
#include "common.h"
#endif


/********************************************************************//**
 * @brief:      scan key process
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void ScanKey(void)
{
  //u8 i,j;
  //u8 l;

  //l = _KEY_PORT_2_;
  //l = (l & _ALL_KEY_MASK_2_);
  //l = 0;
  //i = _KEY_PORT_1_;
  //i = (i & _ALL_KEY_MASK_1_);
  //i = i|l;

  //if (i == _ALL_KEY_MASK_) {
  //  F_PushKey = 0;
  //  F_NewKey    = 0;
  //  F_HoldKey   = 0;
  //  F_TwoKey    = 0;
  //  goto normal_quit_scan_key;
  //}

  if (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN)) {
    F_PushKey = RESET;
    F_NewKey    = RESET;
    F_HoldKey   = RESET;
    F_TwoKey    = RESET;
    goto normal_quit_scan_key;
  }

  DelayMs(2);

  //l = _KEY_PORT_2_;
  //l = (l & _ALL_KEY_MASK_2_);
  //l = 0;
  //j = _KEY_PORT_1_;
  //j = (j & _ALL_KEY_MASK_1_);
  //j = j|l;

  if (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN)) {
    F_PushKey = RESET;
    F_NewKey    = RESET;
    F_HoldKey   = RESET;
    F_TwoKey    = RESET;
    goto normal_quit_scan_key;
  }

  /*
  if (i == j) {
    if ((i & _ALL_KEY_MASK_1_) == 0x00) {
      //push key1
      Key = _KEY_1_;
    }
    //else if ((i & _ALL_KEY_MASK_2_) == 0x00) {
    //  //push key2
    //  Key = _KEY_2_;
    //}
    else {
      //release key
      Key = _NO_KEY_;
    }
  } else {
    //error
    Key = _NO_KEY_;
  }*/

  Key = _KEY_1_;
  if (Key == _NO_KEY_) {
    //Key   = _NO_KEY_;
    //F_PushKey = 0;
    F_NewKey    = RESET;
    F_HoldKey   = RESET;
    F_TwoKey    = RESET;
    goto normal_quit_scan_key;
  } else {
    if (F_PushKey == RESET) {
      OldKey = Key;
      F_NewKey = SET;
      F_PushKey = SET;
      //TEST
      //P10 = 1;
    }
  }

normal_quit_scan_key:
  asm("nop");
}

/********************************************************************//**
 * @brief:          KEY HOLD COM Function subprogram
 *
 *
 * @param[in]:      NONE
 *
 * @return:         NONE
 *********************************************************************/
FlagStatus HoldKeyCom(void)
{
  if (F_NewKey == SET) {
    HoldKeyCtr = 0;
  } else {
    if (F_HoldKey == RESET) {
      if (HoldKeyCtr == _HOLD_TIMER_KEY_) {
        F_HoldKey = SET;
        return SET;
      }
    }
  }

  return RESET;
}

/********************************************************************//**
 * @brief:          push key Function subprogram
 *
 *
 * @param[in]:      NONE
 *
 * @return:         NONE
 *********************************************************************/
void PushKeyFunc(void)
{
  switch (Key)
  {
    case _KEY_1_:
      if (HoldKeyCom()) {

      } else {
        if (F_NewKey == 1) {
          #if (_DELAY_3S_VENT_)
          VentDelay = 0x00;
          #endif
          F_Vent = SET;
        }
      }
      break;
    case _KEY_2_:
      if (HoldKeyCom()) {
        //P3_4 = 0;
        //OldKey = 0x00;
      }
      break;
    default:
      break;
  }

  F_NewKey = RESET;
}

/********************************************************************//**
 * @brief:          rele key Function subprogram
 *
 * @param[in]:  NONE
 *
 * @return:         NONE
 *********************************************************************/
void ReleKeyFunc(void)
{
  INT8U tmp;

  tmp = OldKey;
  OldKey = 0x00;

  switch (tmp)
  {
    case _KEY_1_:
      #if (_DELAY_3S_VENT_)
      VentDelay = _VENT_DELAY_;//(500/10);//0.5S
      F_WaterPumpOn = RESET;
      #else
      VENT_PIN_LOW();
      F_Vent = RESET;
      F_WaterPumpOn = RESET;
      #endif
      break;
    case _KEY_2_:
      //if (SettingCom()) {
        //if (F_NewKey) {
          //GRENN_LED = 0;
          OldKey = 0x00;
        //}
      //}
      break;
    default:
      break;
  }

  OldKey = 0x00;
}
