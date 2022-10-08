#ifndef _ADC_FUNC_H_
#define _ADC_FUNC_H_

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void SetPwmDuty(u16 temp);
u16 KnobSwitch(void);
u8 GetKnobSwitchLevel(void);

void SortRoutine(INT16U a[], INT8U num);
INT16U GetAverageValue(INT16U *ptr, INT8U num);
u16 ADConversion(ADC_Channel_TypeDef channel);

#endif
