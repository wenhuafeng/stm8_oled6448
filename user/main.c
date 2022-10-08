/*
 *******************************************************************************
 * Filename    	: Main.c
 * Processor   	: STM8L051F3
 * Package type : SSOP 20pin
 * Main OSC    	: IRC_16MHz
 * SUB OSC     	: NO
 * Author      	: Wenhuafeng
 * Date        	: 201801010 15:50 ~
 *******************************************************************************
*/

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
#if (_OLED_6448_)
    OLED_Init();
#endif
#if (_NTC_)
    NTC_Init();
#endif
    //PowerOnHeat15S();
    F_PowerUp = SET;

    //TEST
    //TEST

    do {
        if (F_ADC1_ConversionComplete) {
            F_ADC1_ConversionComplete = RESET;
        }
        if (F_10MS) {
            F_10MS = RESET;
            CtrFunc();
#if (_OLED_6448_)
            LCD_P8x16Str(Tbl);
#endif
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
#if (_TH_)
            Temperature = ReadTemperatureSensor();
            TempHeatControl(Temperature);
#endif
#if (_NTC_)
            NTC_Check();
#endif
        }
        if (F_500MS) {
            F_500MS = RESET;
#if (_OLED_6448_)
            OledDisp();
#endif
        }
#if (_SOFTWARE_RTC_)
        if (F_1S) {
            F_1S = RESET;
            Time_Deal();
#if (_UART_FUNC_)
            //uart_send("abc", 3);
            uart_send((&ADC_BUFFER.Buf.adc_buf[0]), 3 * 2);
#endif
        }
#endif
        //V220_Detect();
        //LowPowerRunMode();
        //AutomaticHeatingFunc();
        LED_Management();
        ScanKey();
        if (F_PushKey) {
            if ((Key < _MAX_KEY_) && (Key != _NO_KEY_)) {
                PushKeyFunc();
            }
        } else {
            if ((OldKey < _MAX_KEY_) && (OldKey != _NO_KEY_)) {
                ReleKeyFunc();
            }
        }
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
#if (_DELAY_3S_VENT_)
    if (VentDelay) {
        VentDelay--;
        if (VentDelay == 0x00) {
            VENT_PIN_LOW();
            F_Vent = RESET;
        }
    }
#endif
}

//------------------------------------------------------------------------------
void TempHeatControl(int16_t Temp)
{
    if (F_PushKey == SET) {
        if (Temp < 1200) {
            HeatSpeed = 0;
        } else if (Temp < 1300) {
            HeatSpeed = 0;
        } else if (Temp < 1400) {
            HeatSpeed = 0;
        }

        if (Temp > 1000) {
            F_WaterPumpOn = SET;
        } else {
            F_WaterPumpOn = RESET;
        }

        if (F_Heat == SET) {
            if (Temp > 1500) {
                F_Heat = RESET;
            }
        } else {
            //if (F_PushKey == SET) {
            if (F_Heat == RESET) {
                if (Temp < 1400) {
                    F_Heat = SET;
                }
            }
            //}
        }
    } else {
        if (Temp < 1000) {
            HeatSpeed = 0;
        } else if (Temp < 1100) {
            HeatSpeed = 2;
        } else if (Temp < 1200) {
            HeatSpeed = 4;
        } else {
            HeatSpeed = 4;
        }

        if (F_Heat == SET) {
            if (Temp > 1200) {
                F_Heat = RESET;
            }
        } else {
            //if (F_PushKey == SET) {
            if (F_Heat == RESET) {
                if (Temp < 1100) {
                    F_Heat = SET;
                }
            }
            //}
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