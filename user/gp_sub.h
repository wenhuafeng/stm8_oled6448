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
OS_EXT INT8U DEC[4]; //dec2hex use.
#endif

#ifdef _HEX2DEC
OS_EXT INT8U HEX; //hex2dec use.
#endif

INT8U HexToAsc(INT8U aHex);
INT8U AscToHex(INT8U aChar);

void KEY_TONE(void);
INT8U C24HR_TO_12HR(INT8U hr);
INT16S C2F(INT16S temp);
//void CALC_WEEK (void);
INT16U HPA2INHG(INT16U i);
void HEX2DEC(INT16U Hp);
INT8U DEC2HEX(INT8U HEX_1);

#ifdef _DELAY_US_
void DelayUs(INT8U count);
#endif
#ifdef _DELAY_MS_
void DelayMs(INT16U t);
#endif
#ifdef _DELAY_MS_1_
void DelayMs(u16 n_ms);
#endif
#ifdef _DELAY_US_1_
void DelayUs(u16 n_10us);
#endif

#endif
