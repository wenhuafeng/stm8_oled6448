#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "includes.h"
#endif

static FlagStatus F_10MS;
static FlagStatus F_200MS;
static FlagStatus F_500MS;

static FlagStatus F_AC_DC_PUMP;
static FlagStatus F_WaterPumpOn;

static FlagStatus F_Vent;
static FlagStatus F_Pump;
static FlagStatus F_Heat;

static uint16_t FlowMeterCtr;
static uint8_t HeatSpeed;
static uint16_t VentDelay;
static uint8_t PumpSpeed;

uint8_t COMMON_GetPumpSpeed(void)
{
    return PumpSpeed;
}

void COMMON_PushKeyHeat(int16_t temp)
{
    if (F_Heat == SET) {
        if (temp > 1500) {
            F_Heat = RESET;
        }
    } else {
        if (F_Heat == RESET) {
            if (temp < 1400) {
                F_Heat = SET;
            }
        }
    }
}

void COMMON_ReleKeyHeat(int16_t temp)
{
    if (F_Heat == SET) {
        if (temp > 1200) {
            F_Heat = RESET;
        }
    } else {
        if (F_Heat == RESET) {
            if (temp < 1100) {
                F_Heat = SET;
            }
        }
    }
}

void COMMON_SetWaterPumpOnFlag(FlagStatus flag)
{
    F_WaterPumpOn = flag;
}

void COMMON_SetVentDelay(uint16_t vent)
{
    VentDelay = vent;
    if (vent == 0) {
        F_Vent = SET;
    }
}

void COMMON_VentCountFunc(void)
{
    if (VentDelay) {
        VentDelay--;
        if (VentDelay == 0x00) {
            VENT_PIN_LOW();
            F_Vent = RESET;
        }
    }
}

void COMMON_SetHeatSpeed(uint8_t speed)
{
    HeatSpeed = speed;
}

void COMMON_SetSystickFlag(void)
{
    if (TIM3_GetITStatus(TIM3_IT_Update) == RESET) {
        return;
    }
    TIM3_ClearITPendingBit(TIM3_IT_Update);

    F_10MS = SET;
}

void COMMON_SetRtcFlag(void)
{
    if (RTC_GetITStatus(RTC_IT_WUT) == RESET) {
        return;
    }
    RTC_ClearITPendingBit(RTC_IT_WUT);
    //RTC_WakeUpCmd(DISABLE);

    F_500MS = SET;
}

void COMMON_Count(void)
{
    static uint8_t count = 0;

    count++;
    if (count >= 20) {
        count   = 0x00;
        F_200MS = SET;
    }
}

void COMMON_EXTI6_Process(void)
{
    static uint8_t PumpCtr;
    static uint8_t HeatSpeedCtr;
    uint16_t tmp;

    if (EXTI_GetITStatus(EXTI_IT_Pin6) == RESET) {
        return;
    }
    EXTI_ClearITPendingBit(EXTI_IT_Pin6);

    if (F_AC_DC_PUMP) {
        if (GPIO_ReadInputDataBit(OVER_ZERO_PORT, OVER_ZERO_PIN)) {
            if (F_Pump == RESET) {
                PumpCtr++;
                if (PumpCtr > PumpSpeed) {
                    if (F_WaterPumpOn == SET) {
                        PUMP_PIN_HIGH();
                        F_Pump = SET;
                    }
                }
            } else {
                PUMP_PIN_LOW();
                F_Pump  = RESET;
                PumpCtr = 0x00;
            }
        }
    }

    if (F_Heat == SET) {
        HeatSpeedCtr++;
        if (HeatSpeedCtr > HeatSpeed) {
            HeatSpeedCtr = 0x00;
            HEAT_PIN_HIGH();
        }
    }
    if (F_Vent) {
        VENT_PIN_HIGH();
    }

    for (tmp = 0; tmp < 300; tmp++) {
        asm("nop");
        asm("nop");
    }

    HEAT_PIN_LOW();
}

void COMMON_EXTI7_Process(void)
{
    if (EXTI_GetITStatus(EXTI_IT_Pin7) == RESET) {
        return;
    }
    EXTI_ClearITPendingBit(EXTI_IT_Pin7);

    FlowMeterCtr++;
}

static void LED_Management(void)
{
    if (F_Heat == RESET) {
        RED_LED_OFF();
        GREEN_LED_ON();
    } else {
        RED_LED_ON();
        GREEN_LED_OFF();
    }
}

void COMMON_Init(void)
{
    DelayMs(100);
    OLED_Init();
}

void COMMON_Process(void)
{
    int16_t temp;
    static uint8_t secCount = 0;

    if (F_10MS) {
        F_10MS = RESET;
        COMMON_Count();
        OLED_Display();
    }
    if (F_200MS) {
        F_200MS   = RESET;
        PumpSpeed = GetKnobSwitchLevel();
        F_AC_DC_PUMP = GPIO_ReadInputDataBit(PUMP_SELECT_PORT, PUMP_SELECT_PIN);
        if (F_AC_DC_PUMP == RESET) {
            if (F_WaterPumpOn == SET) {
                SetPwmDuty(KnobSwitch() / 11);
            } else {
                SetPwmDuty(221);
            }
        } else {
            SetPwmDuty(221);
        }

        temp = NTC_ReadSensor();
        TempHeatControl(temp);
    }
    if (F_500MS == SET) {
        F_500MS = RESET;
        secCount++;
        if ((secCount & 0x01) != 0x00) {
            TIME_Run();
        }
        OLED_DispBufferUpdate();
        printf_test();
    }

    LED_Management();
    ScanKey();
    KEY_Process();
}
