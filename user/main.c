/* Head files */
#include "common.h"

CONST uint8_t Version[3] = "300";

//##############################################################################
#warning message "Software_Version: <V300>"
#warning message "Software_Date:    2019/01/12"
#warning message "Software_Project: SC-1086"
#warning message "Software_MCU:     STM8L051F3"
#warning message "Main_OSC:         IRC_16MHz"
#warning message "SUB_OSC:          IRC_32.768KHZ"
#warning message "Author:           wenhuafeng"
//##############################################################################

//------------------------------------------------------------------------------

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
    disableInterrupts();
    Sys_Init();
    enableInterrupts();

    DelayMs(100);
    OLED_Init();
    my_printf_test();

    do {
        if (F_ADC1_ConversionComplete) {
            F_ADC1_ConversionComplete = RESET;
        }
        if (F_10MS) {
            F_10MS = RESET;
            CtrFunc();
            LCD_P8x16Str();
        }
        if (F_200MS) {
            F_200MS   = RESET;
            PumpSpeed = GetKnobSwitchLevel();
            //PumpSpeed = 7;
            F_AC_DC_PUMP = GPIO_ReadInputDataBit(PUMP_SELECT_PORT, PUMP_SELECT_PIN);
            if (F_AC_DC_PUMP == RESET) {
                if (F_WaterPumpOn) {
                    SetPwmDuty(KnobSwitchAdvalue / 11);
                } else {
                    SetPwmDuty(221);
                }
            } else {
                SetPwmDuty(221);
            }

            //Temperature = ReadTemperatureSensor();
            Temperature = NTC_ReadSensor();
            TempHeatControl(Temperature);
        }
        if (F_500MS) {
            F_500MS = RESET;
            OledDisp();
        }
        if (F_1S) {
            F_1S = RESET;
            Time_Deal();
        }

        LED_Management();
        ScanKey();
        KEY_Process();
    } while (1);
}

//------------------------------------------------------------------------------
void LED_Management(void)
{
    if (F_Heat == RESET) {
        RED_LED_OFF();
        GREEN_LED_ON();
    } else {
        RED_LED_ON();
        GREEN_LED_OFF();
    }

    if (F_500MS_LED == SET) {
        F_500MS_LED = RESET;
        //RUN_LED_TOGGLE();
    }
}

//------------------------------------------------------------------------------
void CtrFunc(void)
{
    if (VentDelay) {
        VentDelay--;
        if (VentDelay == 0x00) {
            VENT_PIN_LOW();
            F_Vent = RESET;
        }
    }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1) {
    }
}
#endif