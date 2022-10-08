#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

u8 pwm_num     = _PWM_OUTPUT_OFF_;
u8 pwm_num_bak = _PWM_OUTPUT_OFF_;

/********************************************************************/ /**
 * @brief:      ADC Conversion subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     adc
 *********************************************************************/
void SetPwmDuty(u16 temp)
{
    /* Set the Pulse value */
    TIM2->CCR1H = (uint8_t)(temp >> 8);
    TIM2->CCR1L = (uint8_t)(temp);
}

/********************************************************************/ /**
 * @brief:      Motor On/Off subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     adc
 *********************************************************************/
void WorkOnOff(u8 WorkStatus)
{
    if (WorkStatus == _WORK_OFF_) {
        pwm_num     = _PWM_OUTPUT_OFF_;
        pwm_num_bak = _PWM_OUTPUT_OFF_;
        SetPwmDuty(_PWM_OUTPUT_OFF_);
        LED_PwmGearSet(_LED_PWM_OFF_);
    } else if (WorkStatus == _WORK_LOW_) {
        pwm_num_bak = _PWM_OUTPUT_LOW_;
        LED_PwmGearSet(_LED_LOW_);
        F_WorkStatus = SET;
        LED_SetBatVolInd();
    } else if (WorkStatus == _WORK_MID_) {
        pwm_num_bak = _PWM_OUTPUT_MID_;
        LED_PwmGearSet(_LED_MID_);
        F_WorkStatus = SET;
        LED_SetBatVolInd();
    } else if (WorkStatus == _WORK_HIGH_) {
        pwm_num_bak = _PWM_OUTPUT_HIGH_;
        LED_PwmGearSet(_LED_HIGH_);
        F_WorkStatus = SET;
        LED_SetBatVolInd();
    }
}
