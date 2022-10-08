

#ifndef _TH_TEST_H_
#define _TH_TEST_H_

#define _TEST_TEMP_TIME                 6//30		//30 sec

#define _IN_TEMP_MAX_C                  (+600  )
#define _IN_TEMP_MIN_C                  (-100  )

#define _TEMP_MAX                       (+601  )
#define _TEMP_MIN                       (-101  )

#define TEMP_ADC                        P21
#define TEMP_ADC_NUMBER                 (1 << 1)
#define TEMP_ADC_IN()                   do{P2IO &= ~TEMP_ADC_NUMBER;}while(0)
#define TEMP_ADC_OUT()                  do{P2IO |= TEMP_ADC_NUMBER;}while(0)
#define TEMP_ADC_IO()                   do{P2FSRL &= ~0x0C;}while(0)
#define TEMP_ADC_AD()                   do{P2FSRL |= 0x08;}while(0)

#define TVGain                          1

enum {
  _CURRENT_TEMP_,
  _MAX_TEMP_,
  _MIN_TEMP_,
};

typedef enum {_C_=0, _F_} CF_Flag;
extern CF_Flag F_CF;

extern INT16S InTemp_C;
extern INT16S InMaxTemp_C;
extern INT16S InMinTemp_C;

extern FlagStatus F_InTempFirstTest;
extern FlagStatus F_TempOnOff;
extern INT8U TempStep;

//==============================================================================

INT16S ReadTemperatureSensor(void);
void ProcessTemperatureFunction(void);

#endif


