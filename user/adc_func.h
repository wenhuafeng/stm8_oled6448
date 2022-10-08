#ifndef _ADC_FUNC_H_
#define _ADC_FUNC_H_

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void SetPwmDuty(uint16_t temp);
uint16_t KnobSwitch(void);
uint8_t GetKnobSwitchLevel(void);

void SortRoutine(uint16_t a[], uint8_t num);
uint16_t GetAverageValue(uint16_t *ptr, uint8_t num);
uint16_t ADConversion(ADC_Channel_TypeDef channel);

#endif
