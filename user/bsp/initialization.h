#ifndef _INITIALIZATION_H_
#define _INITIALIZATION_H_

//------------------------------------------------------------------------------
#define BUFFER_SIZE ((uint8_t)3)
//extern uint16_t Buffer[BUFFER_SIZE];

union ADC_BUF {
    uint16_t Buffer[BUFFER_SIZE];
    struct {
        uint8_t adc_buf[BUFFER_SIZE * 2];
    } Buf;
};

//------------------------------------------------------------------------------
//void CLK_Config_LSE(void);
void CLK_Config_LSI(void);
void CLK_Config_HSI(void);

void PortLowPower(void);

void PORT_Config(void);
void Clock_Init(void);
void Sys_Init(void);

void EXTI_Config(void);

#endif
