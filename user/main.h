#ifndef _MAIN_H_
#define _MAIN_H_

#define _PWM_OUTPUT_OFF_  221
#define _PWM_OUTPUT_LOW_  173
#define _PWM_OUTPUT_MID_  103
#define _PWM_OUTPUT_HIGH_ 0

OS_EXT FlagStatus F_10MS;
OS_EXT FlagStatus F_100MS;
OS_EXT FlagStatus F_130MS;
OS_EXT FlagStatus F_130MS_LED;
OS_EXT FlagStatus F_200MS;
OS_EXT FlagStatus F_500MS;
OS_EXT FlagStatus F_500MS_1;
OS_EXT FlagStatus F_500MS_LED;
OS_EXT FlagStatus F_1S;

OS_EXT FlagStatus F_WorkStatus;

OS_EXT FlagStatus F_Protection;

OS_EXT FlagStatus F_WaterPumpOn;
OS_EXT FlagStatus F_Vent;
OS_EXT FlagStatus F_Pump;
OS_EXT FlagStatus F_Heat;

#define _TIME_BASE_xMS_ (10)

#define _VENT_DELAY_ (1000 / _TIME_BASE_xMS_)
OS_EXT uint16_t VentDelay;

#define _15S_ (15000 / _TIME_BASE_xMS_)
OS_EXT uint16_t Ctr15S;

#define _1S_ (1000 / _TIME_BASE_xMS_)

OS_EXT uint8_t PumpSpeed;
OS_EXT uint8_t AutoHeaterCtr;

OS_EXT FlagStatus F_PowerUp;

OS_EXT int16_t Temperature;

OS_EXT uint8_t ThyristorCtr;

OS_EXT uint16_t FlowMeterCtr;

OS_EXT uint16_t KnobSwitchAdvalue;

#define _AC_PUMP_ (SET)
#define _DC_PUMP_ (RESET)
OS_EXT FlagStatus F_AC_DC_PUMP;

OS_EXT uint16_t SecCtr;

#define _CONTINOUS_READ_NUM_OUT_ 10000
#define _CONTINOUS_READ_NUM_IN_  1000
OS_EXT uint16_t ContinousRead220VCtr_1;
OS_EXT uint16_t ContinousRead220VCtr_2;
OS_EXT uint8_t F_220V_OUT;
OS_EXT uint8_t F_220V_IN;

OS_EXT FlagStatus F_ADC1_ConversionComplete;

OS_EXT uint8_t HeatSpeed;
void TempHeatControl(int16_t Temp);

void CtrFunc(void);
void V220_Detect(void);
void LowPowerRunMode(void);
void AutomaticHeatingFunc(void);
void LED_Management(void);
void PowerOnHeat15S(void);

#endif
