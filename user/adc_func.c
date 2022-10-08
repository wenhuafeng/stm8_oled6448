

#ifndef  OS_MASTER_FILE
#define  OS_GLOBALS
#include "common.h"
#endif


/********************************************************************//**
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

/********************************************************************//**
 * @brief:      ADC Conversion subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     adc
 *********************************************************************/
u16 ADConversion(ADC_Channel_TypeDef channel)
{
  u16 adc = 0;

  // Enable ADC1 Channels
  ADC_ChannelCmd(ADC1, channel, ENABLE);
  ADC_SoftwareStartConv(ADC1);
  while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
  ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
  adc = ADC_GetConversionValue(ADC1);
  ADC_ChannelCmd(ADC1, channel, DISABLE);

  return adc;
}

/********************************************************************//**
 * @brief:      Sort Routine
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
void SortRoutine(INT16U a[], INT8U num)
{
  INT8U i,j;
  INT16U tmp;

  for (i=0; i<num-1; i++) {
    for (j=i+1; j<num; j++) {
      tmp = a[i];
      if (tmp > a[j]) {
        a[i] = a[j];
        a[j] = tmp;
      }
    }
  }
}

/********************************************************************//**
 * @brief:      Cal Average Value
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
INT16U GetAverageValue(INT16U *ptr, INT8U num)
{
  INT8U i;
  INT16U sum = 0;
  INT16U average;

  for (i=1; i<num-1; i++) {
    sum += *(ptr + i);
  }

  average = sum / (num -2);
  i = sum % (num - 2);
  if (i > (num-2)/2) {
    average++;
  }

  return (average);
}

/********************************************************************//**
 * @brief:      Slide switch voltage subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     ADC value
 *********************************************************************/
u16 KnobSwitch(void)
{
  u8 i;
  u16 adVal;
  u16 adBuf[5];
  //FP32 Voltage;

  for (i=0; i<5; i++) {
    adBuf[i] = ADConversion(ADC_Channel_4);
  }

  /*Min -> Max,taxis*/
  SortRoutine(adBuf, 5);

  /*delete Min and Max A/D value,calc average*/
  adVal = GetAverageValue(adBuf, 5);

  return (adVal);
}

//========================================================================
#define _ADC_VALUE_1_           0x000
#define _ADC_VALUE_2_           (0xAD6/10*1)
#define _ADC_VALUE_3_           (0xAD6/10*2)
#define _ADC_VALUE_4_           (0xAD6/10*3)
#define _ADC_VALUE_5_           (0xAD6/10*4)
#define _ADC_VALUE_6_           (0xAD6/10*5)
#define _ADC_VALUE_7_           (0xAD6/10*6)
#define _ADC_VALUE_8_           (0xAD6/10*7)
#define _ADC_VALUE_9_           (0xAD6/10*8)
#define _ADC_VALUE_10_          (0xAD6/10*9)
#define _ADC_VALUE_11_          (0xfff)

u16 LEVEL_TBL_1[10] =
{
  _ADC_VALUE_2_,
  _ADC_VALUE_3_,
  _ADC_VALUE_4_,
  _ADC_VALUE_5_,
  _ADC_VALUE_6_,
  _ADC_VALUE_7_,
  _ADC_VALUE_8_,
  _ADC_VALUE_9_,
  _ADC_VALUE_10_,
  _ADC_VALUE_11_,
};

#define _LEVEL_1_ADC_VALUE_     (_ADC_VALUE_1_  + (_ADC_VALUE_2_-_ADC_VALUE_1_)/2)
#define _LEVEL_2_ADC_VALUE_     (_ADC_VALUE_2_  + (_ADC_VALUE_3_-_ADC_VALUE_2_)/2)
#define _LEVEL_3_ADC_VALUE_     (_ADC_VALUE_3_  + (_ADC_VALUE_4_-_ADC_VALUE_3_)/2)
#define _LEVEL_4_ADC_VALUE_     (_ADC_VALUE_4_  + (_ADC_VALUE_5_-_ADC_VALUE_4_)/2)
#define _LEVEL_5_ADC_VALUE_     (_ADC_VALUE_5_  + (_ADC_VALUE_6_-_ADC_VALUE_5_)/2)
#define _LEVEL_6_ADC_VALUE_     (_ADC_VALUE_6_  + (_ADC_VALUE_7_-_ADC_VALUE_6_)/2)
#define _LEVEL_7_ADC_VALUE_     (_ADC_VALUE_7_  + (_ADC_VALUE_8_-_ADC_VALUE_7_)/2)
#define _LEVEL_8_ADC_VALUE_     (_ADC_VALUE_8_  + (_ADC_VALUE_9_-_ADC_VALUE_8_)/2)
#define _LEVEL_9_ADC_VALUE_     (_ADC_VALUE_9_  + (_ADC_VALUE_10_-_ADC_VALUE_9_)/2)
#define _LEVEL_10_ADC_VALUE_    (_ADC_VALUE_10_ + (_ADC_VALUE_11_-_ADC_VALUE_10_)/2)

u16 LEVEL_TBL[10] =
{
  _LEVEL_1_ADC_VALUE_,
  _LEVEL_2_ADC_VALUE_,
  _LEVEL_3_ADC_VALUE_,
  _LEVEL_4_ADC_VALUE_,
  _LEVEL_5_ADC_VALUE_,
  _LEVEL_6_ADC_VALUE_,
  _LEVEL_7_ADC_VALUE_,
  _LEVEL_8_ADC_VALUE_,
  _LEVEL_9_ADC_VALUE_,
  _LEVEL_10_ADC_VALUE_,
};

/********************************************************************//**
 * @brief:      Slide switch voltage subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     Switch level
 *********************************************************************/
u8 GetKnobSwitchLevel(void)
{
  u16 Advalue;
  //u8 num=10;
  u8 i,j;
  u8 temp[3] = {0};

  for (i=0; i<3; i++) {
    Advalue = KnobSwitch();
    KnobSwitchAdvalue = Advalue;
    for (j=0; j<10; j++) {
      if (Advalue < LEVEL_TBL_1[j]) {
        temp[i] = j;
        break;
      }
    }
    //DelayUs(10);
  }

  if ((temp[0] == temp[1]) && (temp[1] == temp[2]) && (temp[2] == j)) {
    return j;
  } else {
    return 0;
  }
}
