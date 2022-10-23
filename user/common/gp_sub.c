#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "includes.h"
#endif

#ifdef DELAY_MS
void DelayMs(uint16_t ms)
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

    while (ms--) {
        while ((TIM4->SR1 & TIM4_SR1_UIF) == 0);
        TIM4->SR1 &= ~TIM4_SR1_UIF;
    }

    /* Disable Counter */
    TIM4->CR1 &= ~TIM4_CR1_CEN;
}
#endif

#ifdef DELAY_US
void DelayUs(uint16_t us)
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

    while (us--) {
        while ((TIM4->SR1 & TIM4_SR1_UIF) == 0)
            ;
        TIM4->SR1 &= ~TIM4_SR1_UIF;
    }

    /* Disable Counter */
    TIM4->CR1 &= ~TIM4_CR1_CEN;
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);
}
#endif
