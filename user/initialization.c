#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

/* Private define ------------------------------------------------------------*/
#define TIM2_PERIOD (uint8_t)220
#define TIM2_PULSE  _PWM_OUTPUT_OFF_     //duty (0=100%,221=0%)
#define TIM3_PERIOD (uint16_t)(1250 - 1) //(16 MHz/128 = 125000Hz, X=0.01ms*125000-1)

/* Private define ------------------------------------------------------------*/
#define ADC1_DR_ADDRESS ((uint16_t)0x5344)
//#define BUFFER_SIZE             ((uint8_t) 2)
#define BUFFER_ADDRESS ((uint16_t)(&ADC_BUFFER.Buffer[0])) //((uint16_t)(&Buffer))
#define ASCII_NUM_0    ((uint8_t)48)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//uint16_t Buffer[BUFFER_SIZE];
//union ADC_BUF ADC_BUFFER;

/*
void PortLowPower(void)
{
  //1~10
  GPIO_Init(SDA_PORT, SDA_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(SCL_PORT, SCL_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(R_LED_PORT, R_LED_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(G_LED_PORT, G_LED_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(G_T_LED_PORT, G_T_LED_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(PWM_PORT, PWM_PIN, GPIO_Mode_Out_PP_Low_Fast);

  //11~20
  GPIO_Init(KNOB_SWITCH_PORT, KNOB_SWITCH_PIN, GPIO_Mode_Out_PP_Low_Fast);//ADC function.
  GPIO_Init(KEY_PORT, KEY_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(V220_DETECT_PORT, V220_DETECT_PIN, GPIO_Mode_Out_PP_Low_Fast);//External pull-down resistor.
  GPIO_Init(FLOW_METER_PORT, FLOW_METER_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(OVER_ZERO_PORT, OVER_ZERO_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(VENT_PORT, VENT_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(PUMP_PORT, PUMP_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(HEAT_PORT, HEAT_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(PUMP_SELECT_PORT, PUMP_SELECT_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(NTC_PORT, NTC_PIN, GPIO_Mode_Out_PP_Low_Fast);
}
*/

/**
  * @brief  Configure Port peripheral
  * @param  None
  * @retval None
  */
void PORT_Config(void)
{
    //1~10
    GPIO_Init(RED_LED_PORT, RED_LED_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(COM_PORT, COM_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(KEY_PORT, KEY_PIN, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(OUT_PORT, OUT_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(MOTOR_PWM_PORT, MOTOR_PWM_PIN, GPIO_Mode_Out_PP_Low_Fast);

    //11~20
    GPIO_Init(KNOB_SWITCH_PORT, KNOB_SWITCH_PIN, GPIO_Mode_In_FL_No_IT); //ADC function.
    GPIO_Init(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(FLOW_METER_PORT, FLOW_METER_PIN, GPIO_Mode_Out_PP_Low_Fast); //GPIO_Mode_In_PU_IT);
    GPIO_Init(OVER_ZERO_PORT, OVER_ZERO_PIN, GPIO_Mode_In_PU_IT);
    GPIO_Init(VENT_PORT, VENT_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(PUMP_PORT, PUMP_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(HEAT_PORT, HEAT_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(PUMP_SELECT_PORT, PUMP_SELECT_PIN, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(NTC_PORT, NTC_PIN, GPIO_Mode_In_FL_No_IT);

    PUMP_PIN_LOW();
    HEAT_PIN_LOW();
    VENT_PIN_LOW();

    //OLED_SDA_PIN_LOW();
    //OLED_SCL_PIN_LOW();
    PWM_PIN_LOW();
}

/**
  * @brief  Configure Clock peripheral
  * @param  None
  * @retval None
  */
void CLK_Config_HSI(void)
{
    /* Switch the clock to HSI*/
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
    CLK_HSICmd(ENABLE);
    while (((CLK->ICKCR) & 0x02) != 0x02)
        ;
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
    CLK_SYSCLKSourceSwitchCmd(ENABLE);
    while (((CLK->SWCR) & 0x01) == 0x01)
        ;

    CLK_HSEConfig(CLK_HSE_OFF);
    CLK_LSEConfig(CLK_LSE_OFF);
}

/**
  * @brief  Configure ADC peripheral
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
    /* Enable ADC1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);

    /* Enable ADC1 internal Vref*/
    ADC_VrefintCmd(ENABLE);
    /* Initialize and configure ADC1 */
    ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit, ADC_Prescaler_2);
    /* Enable ADC1 Sampling Time */
    ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_384Cycles);
    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);
}

#if 0
/**
  * @brief  Configure ADC peripheral
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
  /* Enable ADC1 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);

  /* Enable ADC1 internal Vref*/
  ADC_VrefintCmd(ENABLE);
  /* Initialize and configure ADC1 */
  ADC_Init(ADC1, ADC_ConversionMode_Continuous, ADC_Resolution_12Bit, ADC_Prescaler_2);
  /* Enable ADC1 Sampling Time */
  ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_96Cycles);
  /* Enable ADC1 Sampling Time */
  //ADC_SamplingTimeConfig(ADC1, ADC_Group_FastChannels, ADC_SamplingTime_96Cycles);
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 Channels 4 */
  ADC_ChannelCmd(ADC1, ADC_Channel_4, ENABLE);  /* connected to Potentiometer knob switch */
  /* Enable ADC1 Channels 17 */
  ADC_ChannelCmd(ADC1, ADC_Channel_17, ENABLE); /* connected to Potentiometer temperature */
  /* Enable ADC1 Channels Vrefint */
  ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, ENABLE); /* connected to  */
}

/**
  * @brief  Configure DMA peripheral
  * @param  None
  * @retval None
  */
static void DMA_Config(void)
{
  /* Enable DMA1 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);

  /* Connect ADC to DMA channel 0 */
  SYSCFG_REMAPDMAChannelConfig(REMAP_DMA1Channel_ADC1ToChannel0);

  DMA_Init(DMA1_Channel0, BUFFER_ADDRESS,
           ADC1_DR_ADDRESS,
           BUFFER_SIZE,
           DMA_DIR_PeripheralToMemory,
           DMA_Mode_Circular,
           DMA_MemoryIncMode_Inc,
           DMA_Priority_High,
           DMA_MemoryDataSize_HalfWord);

  /* DMA Channel0 enable */
  DMA_Cmd(DMA1_Channel0, ENABLE);

  /* Enable DMA1 channel0 Transfer complete interrupt */
  DMA_ITConfig(DMA1_Channel0, DMA_ITx_TC, ENABLE);

  /* DMA enable */
  DMA_GlobalCmd(ENABLE);

  /* Enable ADC1 DMA requests*/
  ADC_DMACmd(ADC1, ENABLE);

  ADC_SoftwareStartConv(ADC1);
}
#endif

/**
  * @brief  Configure TIM2 peripheral
  * @param  None
  * @retval None
  */
static void TIM2_Config(void)
{
    /* TIM2 configuration:
     - TIM2 ETR is mapped to LSE
     - TIM2 counter is clocked by LSE div 4
      so the TIM2 counter clock used is LSE / 4 = 32.768 / 4 = 8.192 KHz
    TIM2 Channel1 output frequency = TIM2CLK / (TIM2 Prescaler * (TIM2_PERIOD + 1))
                                   = 8192 / (1 * 8) = 1024 Hz */

    /* Enable TIM2 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);

    /* Time Base configuration */
    TIM2_DeInit();
    TIM2_TimeBaseInit(TIM2_Prescaler_128, TIM2_CounterMode_Up, TIM2_PERIOD);
    //TIM2_ETRClockMode2Config(TIM2_ExtTRGPSC_DIV4, TIM2_ExtTRGPolarity_NonInverted, 0);
    //TIM2_InternalClockConfig();

    /* Channel 1 configuration in PWM1 mode */
    /* TIM2 channel Duty cycle is 100 * TIM2_PULSE / (TIM2_PERIOD + 1) = 100 * 4/8 = 50 % */
    TIM2_OC1Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable, TIM2_PULSE, TIM2_OCPolarity_Low, TIM2_OCIdleState_Set);
    //TIM2_OC2Init(TIM2_OCMode_PWM2, TIM2_OutputState_Enable, TIM2_PULSE, TIM2_OCPolarity_Low, TIM2_OCIdleState_Set);

    /* TIM2 Main Output Enable */
    TIM2_CtrlPWMOutputs(ENABLE);

    /* TIM2 counter enable */
    TIM2_Cmd(ENABLE);
}

/**
  * @brief  Configure TIM3 peripheral
  * @param  None
  * @retval None
  */
static void TIM3_Config(void)
{
    /* Enable TIM3 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);

    /* Time Base configuration */
    TIM3_DeInit();
    TIM3_TimeBaseInit(TIM3_Prescaler_128, TIM3_CounterMode_Up, TIM3_PERIOD);
    //TIM2_ETRClockMode2Config(TIM2_ExtTRGPSC_DIV4, TIM2_ExtTRGPolarity_NonInverted, 0);
    //TIM2_InternalClockConfig();

    /* Channel 1 configuration in PWM1 mode */
    /* TIM2 channel Duty cycle is 100 * TIM2_PULSE / (TIM2_PERIOD + 1) = 100 * 4/8 = 50 % */
    //TIM3_OC1Init(TIM3_OCMode_PWM1, TIM2_OutputState_Enable, TIM2_PULSE, TIM2_OCPolarity_Low, TIM2_OCIdleState_Set);
    //TIM2_OC2Init(TIM2_OCMode_PWM2, TIM2_OutputState_Enable, TIM2_PULSE, TIM2_OCPolarity_Low, TIM2_OCIdleState_Set);

    /* TIM2 Main Output Enable */
    //TIM2_CtrlPWMOutputs(ENABLE);

    /* TIM2 counter enable */
    //TIM3_Cmd(ENABLE);

    TIM3_ARRPreloadConfig(ENABLE);
    TIM3_ITConfig(TIM3_IT_Update, ENABLE);
    TIM3_Cmd(ENABLE);
}

#if (_MY_PRINTF_FUNC_ || _SYS_PRINTF_FUNC_)
static void USART_Config(void)
{
    /* Enable USART1 clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);

    /* USART1 Port A */
    SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA, ENABLE);
    /* USART1 Reset */
    USART_DeInit(USART1);
    /* USART1 Init */
    USART_Init(USART1, BAUDRATE, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No,
               (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
    /* USART1 Enable single wire(Half-Duplex) */
    USART_HalfDuplexCmd(USART1, ENABLE);
    /* USART1 Enable */
    USART_Cmd(USART1, ENABLE);
    /* USART1 Send byte */
    //USART_SendData8(USART1, '\r');
    //uart_send('\r',1);
    //while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    /* USART1 Rx INT Enable */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
#endif

void EXTI_Config(void)
{
    EXTI_DeInit();
    EXTI_SetPinSensitivity(EXTI_Pin_7, EXTI_Trigger_Rising);         //Flow meter
    EXTI_SetPinSensitivity(EXTI_Pin_6, EXTI_Trigger_Rising_Falling); //Over zero
}

/**
  * @brief  Wait 1 sec for LSE stabilisation .
  * @param  None.
  * @retval None.
  * Note : TIM4 is configured for a system clock = 2MHz
  */
void LSE_StabTime(void)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);

    /* Configure TIM4 to generate an update event each 1 s */
    TIM4_TimeBaseInit(TIM4_Prescaler_16384, 123);
    /* Clear update flag */
    TIM4_ClearFlag(TIM4_FLAG_Update);

    /* Enable TIM4 */
    TIM4_Cmd(ENABLE);

    /* Wait 1 sec */
    while (TIM4_GetFlagStatus(TIM4_FLAG_Update) == RESET)
        ;

    TIM4_ClearFlag(TIM4_FLAG_Update);

    /* Disable TIM4 */
    TIM4_Cmd(DISABLE);

    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);
}

void RTC_Config(void)
{
    /*
  // Enable RTC clock
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
  // Wait for LSE clock to be ready
  while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);
  // wait for 1 second for the LSE Stabilisation
  LSE_StabTime();
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);

  // Configures the RTC wakeup timer_step = RTCCLK/16 = LSE/16 = 488.28125 us
  RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);

  // Enable wake up unit Interrupt
  RTC_ITConfig(RTC_IT_WUT, ENABLE);

  RTC_SetWakeUpCounter(1023);
  RTC_WakeUpCmd(ENABLE);
  */

    CLK_LSICmd(ENABLE);
    // Enable RTC clock
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
    // Wait for LSE clock to be ready
    while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == RESET);
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
    // Configures the RTC wakeup timer_step = RTCCLK/16 = LSE/16 = 488.28125 us
    RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);
    // Enable wake up unit Interrupt
    RTC_ITConfig(RTC_IT_WUT, ENABLE);
    //38000/16=2375, 0.5/(1/2375)=1187.5
    RTC_SetWakeUpCounter(1186);
    RTC_WakeUpCmd(ENABLE);
}

/**
  * @brief  Configure all peripheral
  * @param  None
  * @retval None
  */
void Sys_Init(void)
{
    CLK_Config_HSI();
    RTC_Config();
    PORT_Config();
    EXTI_Config();
    ADC_Config();
    //DMA_Config();
    TIM2_Config();
    TIM3_Config();
#if (_UART_FUNC_)
    USART_Config();
#endif
}
