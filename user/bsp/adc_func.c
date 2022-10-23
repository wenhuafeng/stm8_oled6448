#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "includes.h"
#endif

#define _ADC_VALUE_1_  0x000
#define _ADC_VALUE_2_  (0xAD6 / 10 * 1)
#define _ADC_VALUE_3_  (0xAD6 / 10 * 2)
#define _ADC_VALUE_4_  (0xAD6 / 10 * 3)
#define _ADC_VALUE_5_  (0xAD6 / 10 * 4)
#define _ADC_VALUE_6_  (0xAD6 / 10 * 5)
#define _ADC_VALUE_7_  (0xAD6 / 10 * 6)
#define _ADC_VALUE_8_  (0xAD6 / 10 * 7)
#define _ADC_VALUE_9_  (0xAD6 / 10 * 8)
#define _ADC_VALUE_10_ (0xAD6 / 10 * 9)
#define _ADC_VALUE_11_ (0xfff)

uint16_t LEVEL_TBL_1[10] = {
    _ADC_VALUE_2_, _ADC_VALUE_3_, _ADC_VALUE_4_, _ADC_VALUE_5_,  _ADC_VALUE_6_,
    _ADC_VALUE_7_, _ADC_VALUE_8_, _ADC_VALUE_9_, _ADC_VALUE_10_, _ADC_VALUE_11_,
};

void SetPwmDuty(uint16_t temp)
{
    /* Set the Pulse value */
    TIM2->CCR1H = (uint8_t)(temp >> 8);
    TIM2->CCR1L = (uint8_t)(temp);
}

uint16_t ADConversion(ADC_Channel_TypeDef channel)
{
    uint16_t adc = 0;

    // Enable ADC1 Channels
    ADC_ChannelCmd(ADC1, channel, ENABLE);
    ADC_SoftwareStartConv(ADC1);
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    adc = ADC_GetConversionValue(ADC1);
    ADC_ChannelCmd(ADC1, channel, DISABLE);

    return adc;
}

void SortRoutine(uint16_t *buf, uint8_t num)
{
    uint8_t i, j;
    uint16_t tmp;

    for (i = 0; i < num - 1; i++) {
        for (j = i + 1; j < num; j++) {
            tmp = buf[i];
            if (tmp > buf[j]) {
                buf[i] = buf[j];
                buf[j] = tmp;
            }
        }
    }
}

uint16_t GetAverageValue(uint16_t *ptr, uint8_t num)
{
    uint8_t i;
    uint16_t sum = 0;
    uint16_t average;

    for (i = 1; i < num - 1; i++) {
        sum += *(ptr + i);
    }

    average = sum / (num - 2);
    i       = sum % (num - 2);
    if (i > (num - 2) / 2) {
        average++;
    }

    return (average);
}

uint16_t KnobSwitch(void)
{
    uint8_t i;
    uint16_t adVal;
    uint16_t adBuf[5];

    for (i = 0; i < 5; i++) {
        adBuf[i] = ADConversion(ADC_Channel_4);
    }

    /*Min -> Max,taxis*/
    SortRoutine(adBuf, 5);

    /*delete Min and Max A/D value,calc average*/
    adVal = GetAverageValue(adBuf, 5);

    return (adVal);
}

uint8_t GetKnobSwitchLevel(void)
{
    uint16_t Advalue;
    uint8_t i, j;
    uint8_t temp[3] = {0};

    for (i = 0; i < 3; i++) {
        Advalue = KnobSwitch();
        for (j = 0; j < 10; j++) {
            if (Advalue < LEVEL_TBL_1[j]) {
                temp[i] = j;
                break;
            }
        }
    }

    if ((temp[0] == temp[1]) && (temp[1] == temp[2]) && (temp[2] == j)) {
        return j;
    } else {
        return 0;
    }
}

FlagStatus F_ADC1_ConversionComplete;

void ADC_SetConversionCompleteFlag(void)
{
    F_ADC1_ConversionComplete = SET;
}

void ADC_Process(void)
{
    if (F_ADC1_ConversionComplete) {
        F_ADC1_ConversionComplete = RESET;
    }
}
