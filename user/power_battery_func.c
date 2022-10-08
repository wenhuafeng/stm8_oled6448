#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

/********************************************************************/ /**
 * @brief:      charge on/off subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void ChargeOnOff(FlagStatus F_tmp)
{
    if (F_tmp) {
        //charge on.
        CHARGE_CTRL_HIGH();
        F_ChargeOnOff = SET;
    } else {
        //charge off.
        CHARGE_CTRL_LOW();
        F_ChargeOnOff = RESET;
    }
}

#if (_OZ7710_CHG_CHK_)
/********************************************************************/ /**
 * @brief:      Power In/Out Function
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
FlagStatus OZ7710Chg_Check(void)
{
    u8 tmp_1 = 0x00;
    u8 tmp_2 = 0x00;
    FlagStatus F_tmp;

    do {
        if (GPIO_ReadInputDataBit(OZ7710_CHG_PORT, OZ7710_CHG_PIN) == RESET) {
            tmp_1++;
        }
        tmp_2++;
    } while (tmp_2 < 5);

    if (tmp_1 == 5) {
        //OZ7710 charge on
        F_tmp = SET;
    } else {
        //OZ7710 charge off
        F_tmp = RESET;
    }

    return F_tmp;
}
#endif

/********************************************************************/ /**
 * @brief:      Power In/Out Function
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
FlagStatus PowerInOutCheck(void)
{
    u8 tmp_1 = 0x00;
    u8 tmp_2 = 0x00;

    do {
        if (GPIO_ReadInputDataBit(CHARGE_DET_PORT, CHARGE_DET_PIN) == RESET) {
            tmp_1++;
        }
        tmp_2++;
    } while (tmp_2 < 5);

    if (tmp_1 == 5) {
        //DC power in
        F_PowerIn = SET;
    } else {
        //DC power out
        F_PowerIn = RESET;
    }

    return F_PowerIn;
}

/********************************************************************/ /**
 * @brief:      Power In/Out change Function
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
u8 PowerInOut(void)
{
    u8 tmp = _POWER_CONSTANT_;
    u8 ChargeStatus;
    static u8 ChargeStatusBak = _POWER_OUT_;

    if (PowerInOutCheck() == RESET) {
        ChargeStatus = _POWER_OUT_;
    } else {
        ChargeStatus = _POWER_IN_;
    }
    if (ChargeStatus != ChargeStatusBak) {
        if ((ChargeStatus == _POWER_IN_) && (ChargeStatusBak == _POWER_OUT_)) {
            //DC power in change
            tmp       = _POWER_IN_;
            F_PowerIn = SET;
        } else if ((ChargeStatus == _POWER_OUT_) && (ChargeStatusBak == _POWER_IN_)) {
            //DC power out change
            tmp       = _POWER_OUT_;
            F_PowerIn = RESET;
        }
    }
    ChargeStatusBak = ChargeStatus;

    return tmp;
}

/********************************************************************/ /**
 * @brief:      Process Power/Battery Function
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void ProcessPowerBatteryFunction(void)
{
    u8 BatStatus;
    u8 PowerIO;
    u16 PV;

    BatStatus = GetBatteryVoltageLevel();
    PowerIO   = PowerInOut();

    if (PowerIO == _POWER_IN_) {
        WorkOnOff(_WORK_OFF_);
        //DC power voltage check
        PV = ReadPowerVoltage();
        if ((PV > _POWER_VOLTAGE_LOWER_LIMIT_) && (PV < _POWER_VOLTAGE_UPPER_LIMIT_)) {
            ;
        } else {
            LED_PwmGearSet(_LED_PWM_OFF_);
            LED_ChargeStaticSet(_LED_FLASH_);
            F_SystemError = SET;
            return;
        }

        if (BatStatus == _BAT_FULL_) {
            //Battery full
            //Indicator 10S quit
            ChargeOnOff(RESET);
            if (F_StandyMode)
                return;
            if (LED_BatteryIndicatorCtr == 0x00) {
                LED_SetBatVolInd_10S(0x00);
            }
        } else {
            //Battery not full
            //Battery normal charge
            if (F_StandyMode)
                return;
            if (LED_BatteryIndicatorCtr != 0x00)
                return;
            if (F_ChargeTempOver == RESET) {
                ChargeOnOff(SET);
            }
            LED_ChargeStaticSet(_LED_CHARGE_);
        }
    }

    else if (PowerIO == _POWER_OUT_) {
        SlideSwitchBak = GetSlideSwitchLevel();
        ChargeOnOff(RESET);
        LED_SetBatVolInd_10S(0x00);
        F_StandyMode = RESET;
    }

    else {
        if (F_ChargeOnOff) {
            //charge status.
#if (_OZ7710_CHG_CHK_)
            if (OZ7710Chg_Check() == RESET) {
                BatStatus = _BAT_FULL_;
            }
#endif
            if (BatStatus == _BAT_FULL_) {
                //Battery full
                //Indicator 10S quit
                ChargeOnOff(RESET);
                LED_SetBatVolInd_10S(0x00);
            }
        } else {
            //work status.
            if (BatStatus == _BAT_EMPTY_) {
                if (LED_BatteryIndicatorCtr == 0x00) {
                    WorkOnOff(_WORK_OFF_);
                    LED_SetBatVolInd_10S(_LED_BAT_IND_EMPTY_);
                }
            }
        }
        F_StandyMode = RESET;
    }
}
