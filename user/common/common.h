#ifndef COMMON_H
#define COMMON_H

uint8_t COMMON_GetPumpSpeed(void);

void COMMON_PushKeyHeat(int16_t temp);
void COMMON_ReleKeyHeat(int16_t temp);
void COMMON_SetWaterPumpOnFlag(FlagStatus flag);

void COMMON_SetVentDelay(uint16_t vent);
void COMMON_VentCountFunc(void);

void COMMON_SetHeatSpeed(uint8_t speed);
void COMMON_SetSystickFlag(void);
void COMMON_SetRtcFlag(void);
void COMMON_Count(void);
void COMMON_EXTI6_Process(void);
void COMMON_EXTI7_Process(void);

void COMMON_Init(void);
void COMMON_Process(void);

#endif
