

#ifndef _OLED_H_
#define _OLED_H_


//#include "TypeDefine.h"
//#include "stm32f1xx_hal.h"
//#include "stm32f4xx_hal.h"
//#include "vl6180x_def.h"

#define Write         0
#define Read          1

#define HIGH          1
#define LOW           0

enum {
  _ACK_,
  _NACK_,
};

enum {
  _LCD_SDA_INPUT_,
  _LCD_SDA_OUTPUT_,
};
#define LCD_SCL_1            OLED_SCL_PIN
#define LCD_SDA_1            OLED_SDA_PIN
#define LCD_SCL_1_PORT       OLED_SCL_PORT
#define LCD_SDA_1_PORT       OLED_SDA_PORT
#define LCD_SDAIN_1()        do{GPIO_Init(LCD_SDA_1_PORT, LCD_SDA_1, GPIO_Mode_In_FL_No_IT);}while(0)
#define LCD_SDAOUT_1()       do{GPIO_Init(LCD_SDA_1_PORT, LCD_SDA_1, GPIO_Mode_Out_PP_Low_Fast);}while(0)
#define LCD_SCL_1_HIGH()     do{GPIO_SetBits(LCD_SCL_1_PORT, LCD_SCL_1);}while(0)
#define LCD_SCL_1_LOW()      do{GPIO_ResetBits(LCD_SCL_1_PORT, LCD_SCL_1);}while(0)
#define LCD_SDA_1_HIGH()     do{GPIO_SetBits(LCD_SDA_1_PORT, LCD_SDA_1);}while(0)
#define LCD_SDA_1_LOW()      do{GPIO_ResetBits(LCD_SDA_1_PORT, LCD_SDA_1);}while(0)

OS_EXT uint8_t Tbl[24];
OS_EXT uint8_t TblCtr;

//------------------------------------------------------------------------------
void I2C_PinLow(void);

void OLED_Clear(void);
void OLED_OFF(void);
void OLED_Init(void);
void OledDisp(void);
//void LCD_P8x16Str(void);
void LCD_P8x16Str(u8 *Tbl);

#endif

