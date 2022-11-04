/**
 * @file    ws2812.h
 * @author  Frank (pq_liu@foxmail.com)
 * @brief   WS2812
 * @version 0.1
 * @date    2021-01-16
 *
 * @copyright Copyright (c) 2021
 *
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WS2812_H
#define __WS2812_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>

/* Define --------------------------------------------------------------------*/
//Ӳ��spiģ��ws2811ʱ����spi��3λ����ģ��ws281x��һλ���ݣ�
//Ҫ��ϵͳʱ������Ϊ72M����Ƶ������Ϊ32����SPI��ͨ��Ƶ��Ϊ2.25M������һλ���ݵ�ʱ��ԼΪ444���루ns��
//444ns   888ns  ����WS281XоƬ��ͨ��ʱ��
//  __
// |  |_|   0b110  high level
//  _
// | |__|   0b100  low level
#define WS2812_HIG  (0x06)
#define WS2812_LOW  (0x04)
//WS2812������
#define WS2812_NUM   22
/* typedef -------------------------------------------------------------------*/
typedef struct
{
    uint8_t hig;
    uint8_t mid;
    uint8_t low;
} ws2812ColorBit_t;
/**
 * @brief struct WS2812
 *
 */
typedef struct
{
    uint32_t Info;                      //reserve
    union
    {
        uint8_t Buff[9];
        struct
        {
            uint8_t G[3];               //G First
            uint8_t R[3];
            uint8_t B[3];               //
        }RGB;
    }Col[WS2812_NUM];
} ws2812_t;

/* types ---------------------------------------------------------------------*/
extern ws2812_t g_ws2812;

/* macro ---------------------------------------------------------------------*/


/* functions -----------------------------------------------------------------*/
uint32_t WS2812_Color(uint8_t red, uint8_t green, uint8_t blue);
void WS2812_OneSet( uint8_t num, uint32_t RGB );

void WS2812_CloseAll(void);
void WS2812_SetAll(uint32_t RGB);

void WS2812_ColorWipe(uint32_t c, uint16_t wait);

void WS2812_SingleBreatheRainbow(uint16_t wait);
void WS2812_RainbowRotate(uint16_t wait);

void WS2812_TheaterChase(uint32_t c, uint16_t wait);
void WS2812_TheaterChaseRainbow(uint16_t wait);

void WS2812_RandAll(uint16_t wait);
void WS2812_RandColorWipe(uint16_t wait);

#ifdef __cplusplus
}
#endif

#endif /* __WS2812_H */

/******************************** END *****************************************/
