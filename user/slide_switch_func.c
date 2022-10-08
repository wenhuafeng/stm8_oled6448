
#ifndef  OS_MASTER_FILE
#define  OS_GLOBALS
#include "common.h"
#endif

/********************************************************************//**
 * @brief:      Slide Switch Detect
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void SlideSwitchDetect(void)
{
  u8 Switch;
  FlagStatus F_SlideChange = RESET;

  if (F_PowerIn) return;

  Switch = GetSlideSwitchLevel();
  if (SlideSwitchBak != Switch) {
    F_SlideChange = SET;
    if ((SlideSwitchBak == _WORK_OFF_) || (Switch == _WORK_OFF_)) {
      LED_BatteryIndicatorCtr = 0x00;
    }
  }
  SlideSwitchBak = Switch;

  if (LED_BatteryIndicatorCtr) return;

  if (F_SlideChange == SET) {
    if (Switch == _WORK_OFF_) {
      WorkOnOff(_WORK_OFF_);
#if (_EEPROM_FUNC_)
      WriteDataToEEPROM();
#endif
      VBAT_CTRL_LOW();
    }
    else {
      if (F_WorkTempOver == 0) {
        WorkOnOff(Switch);
      }
    }
  } else {

  }
}
