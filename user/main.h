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

OS_EXT FlagStatus F_WaterPumpOn;
OS_EXT FlagStatus F_Vent;
OS_EXT FlagStatus F_Pump;
OS_EXT FlagStatus F_Heat;

#define _TIME_BASE_xMS_ (10)
#define _VENT_DELAY_ (1000 / _TIME_BASE_xMS_)
OS_EXT uint16_t VentDelay;

OS_EXT uint8_t PumpSpeed;

OS_EXT int16_t Temperature;


OS_EXT uint16_t FlowMeterCtr;

OS_EXT uint16_t KnobSwitchAdvalue;

OS_EXT FlagStatus F_AC_DC_PUMP;

OS_EXT FlagStatus F_ADC1_ConversionComplete;

OS_EXT uint8_t HeatSpeed;



void CtrFunc(void);
void V220_Detect(void);
void LowPowerRunMode(void);
void AutomaticHeatingFunc(void);
void LED_Management(void);
void PowerOnHeat15S(void);

#endif
