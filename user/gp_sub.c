


#ifndef  OS_MASTER_FILE
#define  OS_GLOBALS
#include "common.h"
#endif


/********************************************************************//**
  * @brief  delay for some time in ms unit
  * @caller auto_test
  * @param  n_ms is how many ms of time to delay
  * @retval None
 *********************************************************************/
#ifdef _DELAY_MS_1_
void DelayMs(u16 n_ms)
{
/* Init TIMER 4 */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);

/* Init TIMER 4 prescaler: / (2^6) = /64 */
  TIM4->PSCR = 6;

/* HSI div by 1 --> Auto-Reload value: 16M / 64 = 1/4M, 1/4M / 1k = 250*/
  TIM4->ARR = 250;

/* Counter value: 2, to compensate the initialization of TIMER*/
  TIM4->CNTR = 2;

/* clear update flag */
  TIM4->SR1 &= ~TIM4_SR1_UIF;

/* Enable Counter */
  TIM4->CR1 |= TIM4_CR1_CEN;

  while(n_ms--)
  {
    while((TIM4->SR1 & TIM4_SR1_UIF) == 0) ;
    TIM4->SR1 &= ~TIM4_SR1_UIF;
  }

/* Disable Counter */
  TIM4->CR1 &= ~TIM4_CR1_CEN;
}
#endif

/********************************************************************//**
  * @brief  delay for some time in 10us unit(partial accurate)
  * @caller auto_test
  * @param n_10us is how many 10us of time to delay
  * @retval None
 *********************************************************************/
#ifdef _DELAY_US_1_

void DelayUs(u16 n_10us)
{
/* Init TIMER 4 */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);

/* prescaler: / (2^0) = /1 */
  TIM4->PSCR = 0;

/* SYS_CLK_HSI_DIV1 Auto-Reload value: 16M / 1 = 16M, 16M / 100k = 160 */
  TIM4->ARR = 160;

/* Counter value: 10, to compensate the initialization of TIMER */
  TIM4->CNTR = 10;

/* clear update flag */
  TIM4->SR1 &= ~TIM4_SR1_UIF;

/* Enable Counter */
  TIM4->CR1 |= TIM4_CR1_CEN;

  while(n_10us--)
  {
    while((TIM4->SR1 & TIM4_SR1_UIF) == 0) ;
    TIM4->SR1 &= ~TIM4_SR1_UIF;
  }

/* Disable Counter */
  TIM4->CR1 &= ~TIM4_CR1_CEN;
 CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);
}
#endif

/********************************************************************//**
 * @brief:      hex to asc Function subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
#ifdef _HEX_TO_ASC_
INT8U HexToAsc(INT8U aHex)
{
  if ((aHex>=0) && (aHex <= 9))
    aHex += 0x30;
  else if ((aHex >= 10) && (aHex <= 15))
    aHex += 0x37;
  else
  aHex = 0xff;

  return aHex;
}
#endif

/********************************************************************//**
 * @brief:      asc to hex Function subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
#ifdef _ASC_TO_HEX_
INT8U AscToHex(INT8U aChar)
{
  if ((aChar >= 0x30) && (aChar <= 0x39))
    aChar -= 0x30;
  else if ((aChar >= 0x41) && (aChar <= 0x46))
    aChar -= 0x37;
  else if ((aChar >= 0x61) && (aChar <= 0x66))
    aChar -= 0x57;
  else
  aChar = 0xff;

  return aChar;
}
#endif

/********************************************************************//**
 * @brief:      delay US Function subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
#ifdef _DELAY_US

void DelayUs (INT8U count)
{
  //count = count*20;

  while(count--);
}

#endif

/********************************************************************//**
 * @brief:      DELAY MS
 *
 * @param[in]:  NONE
 *
 * @return:     NONE
 *********************************************************************/
#ifdef _DELAY_MS

void DelayMs(INT16U t)		//��ʾ������������8MHZ��
{
  /*
  //8M
  INT8U i,j;
  for(; t > 0; t--)
  for(j = 21; j > 0; j--)
  for(i = 90; i > 0; i--);
  */

  //16M
  INT8U i,j;
  for(; t > 0; t--)
  for(j = 20; j > 0; j--)
  for(i = 199; i > 0; i--);
}

/*
void DelayMs (INT8U count)
{
  INT16U i;

#if (SystemCoreClock == _4M)
  do {

  	i = 250;
  	do {
  		;
  	} while (--i != 0);

  	;
  } while (--count != 0);
#endif

#if (SystemCoreClock == _8M)
  do {

  	i = 488;
  	do {
  		;
  	} while (--i != 0);

  	;
  } while (--count != 0);
#endif

#if (SystemCoreClock == _12M)
  do {

  	i = 560;
  	do {
  		NOP;
  	} while (--i != 0);

  	;
  } while (--count != 0);
#endif
}
*/

#endif

/********************************************************************//**
 * @brief:      24HR to 12HR Function subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     12HR
 *********************************************************************/
#ifdef _C24HR_TO_12HR

INT8U C24HR_TO_12HR (INT8U hr)
{
  INT8U val;

  if (hr <= 11) {
    F_AM_PM = _AM;
    if (hr == 0) {
      val = 12;
    } else {
      val = hr;
    }
  } else {
    F_AM_PM = _PM;
    if (hr == 12) {
      val = hr;
    } else {
      val = hr - 12;
    }
  }

  return val;
}

#endif

/********************************************************************//**
 * @brief:      C to F Function subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     F
 *********************************************************************/
#ifdef _C2F

INT16S C2F (INT16S temp)
{
  return (temp * 18 + 320);
}

#endif
/********************************************************************//**
 * @brief:      Calculate weekday Function subprogram
 *              Weekday={(Year+12)+Day+(Year+12)/4+T[Mtab]-1}Mod7
 *              If Month<3 The Year Sub 1
 *
 * @param[in]:  Year,Month Offset(Mtab),Day
 *              1990<=Year<=2099, 1<=Month<=12, 1<=Day<=31
 *
 * @return:     WEEK(0=Sunday,1=Monday,...,6=Saturday)
 *********************************************************************/
#ifdef _CALC_WEEK

//week table
CONST INT8U WEEK_TAB_ADDR[13] = {0x00,0x00,0x03,0x02,0x05,0x00,0x03,0x05,0x01,0x04,0x06,0x02,0x04};

//calculate week
void CALC_WEEK (void)
{
  INT16U	tmp1,tmp2,tmp3;

  tmp1 = DEC2HEX(D_YEAR);
  tmp2 = DEC2HEX(D_MONTH);
  tmp3 = DEC2HEX(D_DAY);

  D_WEEK = (tmp1+tmp3+(tmp1/4)+WEEK_TAB_ADDR[tmp2]-1)%7;
}

#endif
/********************************************************************//**
 * @brief:      Pressure HPA->INHG Function subprogram
 *
 * @param[in]:  NONE
 *
 * @return:     DEC[4]
 *********************************************************************/
#ifdef _HPA2INHG

INT16U HPA2INHG (INT16U i)
{
  return (i * 2953 / 1000);
}

#endif
/********************************************************************//**
 * @brief:      HEX TO DEC Function subprogram
 *
 *
 * @param[in]:  Hp(HEX Point)
 *
 * @return:     DEC[4]
 *********************************************************************/
#ifdef _HEX2DEC

void HEX2DEC (INT16U Hp)
{
  INT16U i;

  i = Hp;
  DEC[0] = 0;
  DEC[1] = 0;
  DEC[2] = 0;
  DEC[3] = 0;

  while(i >= 1000){
    i = i - 1000;
    DEC[3]++;
  }
  while(i >= 100){
    i = i - 100;
    DEC[2]++;
  }
  while(i >= 10){
    i = i - 10;
    DEC[1]++;
  }

  DEC[0] = i;
}

#endif

/********************************************************************//**
 * @brief:      DEC TO Hex Function subprogram
 *
 * @param[in]:  HEX
 *
 * @return:     HEX
 *********************************************************************/
#ifdef _DEC2HEX

INT8U DEC2HEX (INT8U HEX_1)
{
  INT8U i;

  i = HEX_1 & 0xf0;
  i = i>>4;

  HEX_1 = HEX_1 & 0x0f;

  while (i != 0) {
    i--;
    HEX_1 = HEX_1+0x0a;
  }

  return HEX_1;
}

#endif





