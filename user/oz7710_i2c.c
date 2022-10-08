

#ifndef  OS_MASTER_FILE
#define  OS_GLOBALS
#include "common.h"
#endif


#if (_OZ7710_)


/********************************************************************//**
 * @brief:     IIC function
 *
 * @param[in]: NONE
 *
 * @return:    NONE
 *********************************************************************/
void IIC_Start(void)
{
  SDAOUT();
  DelayUs(5);
  SDIO = 1;
  DelayUs(2);
  SCLK = 1;
  DelayUs(2);
  SDIO = 0;
  DelayUs(2);
  SCLK = 0;
  DelayUs(5);
}

void IIC_Stop(void)
{
  SDAOUT();
  DelayUs(5);
  SDIO = 0;
  SCLK = 1;
  DelayUs(2);
  SDIO = 1;
  DelayUs(5);
  SCLK = 1;
}

void IIC_SendByte(u8 dat)
{
  u8 i;

  SDAOUT();
  DelayUs(10);
  for(i = 0; i < 8; i++)
  {
    SCLK = 0;
    SDIO = (BOOLEAN)(dat & 0x80);
    DelayUs(5);
    SCLK = 1;
    DelayUs(2);
    dat = dat << 1;
  }
  SCLK = 0;
}

u8 IIC_ReceiveByte(u8 remaining_bytes)
{
  u8 result = 0;
  u8 i,j;

  SDAIN();
  DelayUs(10);
  for(i=0; i<8; i++)
  {
    result = result << 1;
    SCLK = 0;
    DelayUs(2);
    SCLK = 1;
    DelayUs(5);
    j = SDA_PORT;
    if ((j & SDA_NUMBER) == SDA_NUMBER) {
      result = result + 1;
    }
  }
  SCLK = 0;

  SDAOUT();
  DelayUs(5);
  if (remaining_bytes == 0) {
    SDIO = 1;
  } else {
    SDIO = 0;
  }
  DelayUs(2);
  SCLK = 1;
  DelayUs(2);
  SCLK = 0;

  return result;
}

BOOLEAN IIC_Ack(void)
{
  BOOLEAN result;

  SDAIN();
  DelayUs(10);
  SCLK = 1;
  DelayUs(2);
  result = SDIO;
  SCLK = 0;

  return result;
}

/*
void IIC_WriteData(u8 RegAddr, u16 Data)
{
  u8 Data_H = Data;
  u8 Data_L = (Data >> 8);

  IIC_Start();
  IIC_SendByte(IICSENB0Address + Write);
  if (IIC_Ack() == 0) {
    IIC_SendByte(RegAddr);
    if (IIC_Ack() == 0) {
      IIC_SendByte(Data_H);
      if (IIC_Ack() == 0) {
        IIC_SendByte(Data_L);
        IIC_Ack();
      } else {
        SCLK = 0;
      }
    } else {
      SCLK = 0;
    }
  } else {
    SCLK = 0;
  }
  IIC_Stop();
}

u16 IIC_ReadData(u8 RegAddr)
{
  u8  readdata_low;
  u8  CRC8;
  u16 readdata,readdata_high;

  IIC_Start();
  IIC_SendByte(IICSENB0Address + Write);
  if (IIC_Ack() == 0) {
    IIC_SendByte(RegAddr);
    if (IIC_Ack() == 0) {
      IIC_Start();
      IIC_SendByte(IICSENB0Address + Read);
      if (IIC_Ack() == 0) {
        readdata_high = IIC_ReceiveByte(1);
        readdata_low = IIC_ReceiveByte(1);
        CRC8 = IIC_ReceiveByte(0);
      } else {
        SCLK = 0;
        return(0x0000);
      }
    } else {
      SCLK = 0;
      return(0x0000);
    }
  } else {
    SCLK = 0;
    return(0x0000);
  }

  IIC_Stop();
  readdata = (readdata_high << 8);
  readdata |= readdata_low;

  return(readdata);
}
*/

/********************************************************************//**
 * @brief:     OZ7710 function
 *
 * @param[in]: NONE
 *
 * @return:    NONE
 *********************************************************************/



#endif

