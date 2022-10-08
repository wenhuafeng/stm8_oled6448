/**
  ******************************************************************************
  * @file    WWDG/WWDG_RearmReset/stm8l15x_it.c
  * @author  MCD Application Team
  * @version V1.5.2
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#ifndef  OS_MASTER_FILE
#define  OS_GLOBALS
#include "common.h"
#endif

#include "stm8l15x_it.h"

/** @addtogroup STM8L15x_StdPeriph_Examples
  * @{
  */

/** @addtogroup WWDG_RearmReset
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO FunctionalState NonAlowedRefresh;
extern __IO FunctionalState AllowedRefresh;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(NonHandledInterrupt, 0)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif

/**
  * @brief TRAP interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(FLASH_IRQHandler, 1)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief DMA1 channel0 and channel1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL0_1_IRQHandler, 2)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  if (DMA_GetITStatus(DMA1_IT_TC0)) {
    F_ADC1_ConversionComplete = SET;
    /* Clear IT Pending Bit */
    DMA_ClearITPendingBit(DMA1_IT_TC0);
  }

}

/**
  * @brief DMA1 channel2 and channel3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL2_3_IRQHandler, 3)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler, 4)
{
  static u8 i;

  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  //RTC_WakeUpCmd(DISABLE);

  F_500MS = SET;
  F_500MS_1 = SET;
  F_500MS_LED = SET;
  //F_SET_COL = ~F_SET_COL;

  if (++i & 0x01) {
    F_1S = SET;

  }

  RTC_ClearITPendingBit(RTC_IT_WUT);
}

/**
  * @brief External IT PORTE/F and PVD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIE_F_PVD_IRQHandler, 5)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PORTB / PORTG Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIB_G_IRQHandler, 6)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PORTD /PORTH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_H_IRQHandler, 7)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI0_IRQHandler, 8)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI1_IRQHandler, 9)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
#ifdef USE_STM8L1526_EVAL
  /* Turn off LED2 */
  STM_EVAL_LEDOff(LED2);
  /* Disable refreshing WWDG in allowed window */
  AllowedRefresh = DISABLE;

  /* clear Interrupt pending bit */
  EXTI_ClearITPendingBit(EXTI_IT_Pin1);

#elif defined USE_STM8L1528_EVAL

  /* Turn off LED2 */
  STM_EVAL_LEDOff(LED2);
  /* Enable refreshing WWDG in non allowed window */
  NonAlowedRefresh = ENABLE;

  /* clear Interrupt pending bit */
  EXTI_ClearITPendingBit(EXTI_IT_Pin1);
#endif /* USE_STM8L152X_EVAL */
}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI2_IRQHandler, 10)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */

  EXTI_ClearITPendingBit(EXTI_IT_Pin2);
}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI3_IRQHandler, 11)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI4_IRQHandler, 12)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
#ifdef USE_STM8L1526_EVAL
  /* Turn off LED2 */
  STM_EVAL_LEDOff(LED2);
  /* Enable refreshing WWDG in non allowed window */
  NonAlowedRefresh = ENABLE;

  /* clear Interrupt pending bit */
  EXTI_ClearITPendingBit(EXTI_IT_Pin4);
#endif /* USE_STM8L1526_EVAL */
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI5_IRQHandler, 13)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI6_IRQHandler, 14)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  static u8 PumpCtr;
  static u8 HeatSpeedCtr;
  u16 tmp;

  if (F_AC_DC_PUMP) {
    //#if (_AC_DC_PUMP_ == _AC_PUMP_)
      if (GPIO_ReadInputDataBit(OVER_ZERO_PORT, OVER_ZERO_PIN)) {
        //if (F_Protection == 0) {
          //if (F_15S) {
            if (!F_Pump) {
              PumpCtr++;
              if (PumpCtr > PumpSpeed) {
                if (F_WaterPumpOn) {
                  PUMP_PIN_HIGH();
                  F_Pump = SET;
                }
              }
            } else {
              PUMP_PIN_LOW();
              F_Pump = RESET;
              PumpCtr = 0x00;
            }
          //}
        //}
      }
    /*
    #else
      //if (F_15S) {
        PumpCtr++;
        if (PumpCtr > PumpSpeed) {
          PumpCtr = 0x00;
          if (F_WaterPumpOn) {
            PUMP_PIN_HIGH();
            F_Pump = SET;
          }
        }
      //}
    #endif
    */
  }

  if (F_Heat) {
    HeatSpeedCtr++;
    if (HeatSpeedCtr > HeatSpeed) {
      HeatSpeedCtr = 0x00;
      HEAT_PIN_HIGH();
    }
  }
  if (F_Vent) {
    VENT_PIN_HIGH();
  }

  for (tmp=0; tmp<300; tmp++) {
    asm("nop");
    asm("nop");
  }
  //ThyristorCtr = 200;

  #if (!_AC_DC_PUMP_)
  PUMP_PIN_LOW();
  #endif
  HEAT_PIN_LOW();

  //RUN_LED_TOGGLE();//TEST
  EXTI_ClearITPendingBit(EXTI_IT_Pin6);
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI7_IRQHandler, 15)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  if (EXTI_GetITStatus(EXTI_IT_Pin7)) {
    FlowMeterCtr++;

    EXTI_ClearITPendingBit(EXTI_IT_Pin7);
  }

}

/**
  * @brief LCD /AES Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(LCD_AES_IRQHandler, 16)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief CLK switch/CSS/TIM1 break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SWITCH_CSS_BREAK_DAC_IRQHandler, 17)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief ADC1/Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(ADC1_COMP_IRQHandler, 18)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief TIM2 Update/Overflow/Trigger/Break /USART2 TX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler, 19)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer2 Capture/Compare / USART2 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_CC_USART2_RX_IRQHandler, 20)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler, 21)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  //static u8 i;
  static u8 Ctr;
  static u8 Ctr1;
  static u8 Ctr2;

  if (TIM3_GetITStatus(TIM3_IT_Update) == SET) {
    TIM3_ClearITPendingBit(TIM3_IT_Update);

    F_10MS = SET;
    Ctr++;
    if (Ctr > 50) {
      Ctr = 0x00;
      //HoldKeyCtr++;
      /*
      F_500MS = SET;
      F_500MS_1 = SET;
      F_500MS_LED = SET;
      if (++i & 0x01) {
        F_1SEC = SET;
      }
      */
    }
    Ctr1++;
    if (Ctr1 > 10) {
      Ctr1 = 0x00;
      F_100MS = SET;
    }
    Ctr2++;
    if (Ctr2 > 20) {
      Ctr2 = 0x00;
      F_200MS = SET;
    }

    //CtrFunc();
    //LED1_TOGGLE();//TEST
  }
//  else if (USART_GetITStatus(USART1, USART_IT_TC) == SET) {
//    USART_ClearITPendingBit(USART1, USART_IT_TC);
//  }
}

/**
  * @brief Timer3 Capture/Compare /USART3 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_CC_USART3_RX_IRQHandler, 22)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief TIM1 Update/Overflow/Trigger/Commutation Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_COM_IRQHandler, 23)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief TIM1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CC_IRQHandler, 24)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief TIM4 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler, 25)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief SPI1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI1_IRQHandler, 26)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief USART1 TX / TIM5 Update/Overflow/Trigger/Break Interrupt  routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler, 27)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief USART1 RX / Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler, 28)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */

#if (_UART_FUNC_)
  u8 i;

  if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    if (g_uart_rxbuf.len>=sizeof(g_uart_rxbuf.buf)) {
       USART_ReceiveData8(USART1);
       return;
       //goto enable_rx_int;
    }
    i = USART_ReceiveData8(USART1);
    g_uart_rxbuf.buf[g_uart_rxbuf.len++] = i;
    if (i == '5') {
      uart_send("ABC", 3);
    }
  }
#endif

//enable_rx_int:
  //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

/**
  * @brief I2C1 / SPI2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C1_SPI2_IRQHandler, 29)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/