#ifndef _GP_SUB_H_
#define _GP_SUB_H_

#define _DELAY_US_1_
#define _DELAY_MS_1_

//#define _HEX_TO_ASC_
//#define _ASC_TO_HEX_
//#define _DELAY_US
//#define _DELAY_MS
//#define _C24HR_TO_12HR
//#define _C2F
//#define _CALC_WEEK
//#define _HPA2INHG
//#define _HEX2DEC
//#define _DEC2HEX

#ifdef _DEC2HEX
OS_EXT uint8_t DEC[4]; //dec2hex use.
#endif

#ifdef _HEX2DEC
OS_EXT uint8_t HEX; //hex2dec use.
#endif

uint8_t HexToAsc(uint8_t aHex);
uint8_t AscToHex(uint8_t aChar);

void KEY_TONE(void);
uint8_t C24HR_TO_12HR(uint8_t hr);
int16_t C2F(int16_t temp);
//void CALC_WEEK (void);
uint16_t HPA2INHG(uint16_t i);
void HEX2DEC(uint16_t Hp);
uint8_t DEC2HEX(uint8_t HEX_1);

#ifdef _DELAY_US_
void DelayUs(uint8_t count);
#endif
#ifdef _DELAY_MS_
void DelayMs(uint16_t t);
#endif
#ifdef _DELAY_MS_1_
void DelayMs(uint16_t n_ms);
#endif
#ifdef _DELAY_US_1_
void DelayUs(uint16_t n_10us);
#endif

#endif
