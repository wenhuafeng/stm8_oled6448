


#ifndef _OZ7710_IIC_H_
#define _OZ7710_IIC_H_


#define SCLK                  P3_4
#define SDIO                  P3_5
#define SDA_PORT              P3
#define SDA_NUMBER            (1 << 5)
#define SDAIN()               do{P35_INPUT();}while(0)
#define SDAOUT()              do{P35_OUTPUT();}while(0)
#define SCLIN()               do{P34_INPUT();}while(0)
#define SCLOUT()              do{P34_OUTPUT();}while(0)

#define IICSENB0Address       0x42

#define HIGH                  1
#define LOW                   0

#define Write                 0
#define Read                  1

//---------------------------------------------------------------------------------------
void IIC_Init();
void IIC_Start();
void IIC_Stop();
void IIC_SendByte(u8 dat);
u8 IIC_ReceiveByte(u8 remaining_bytes);
BOOLEAN IIC_Ack(void);

//void IIC_WriteData(u8 NumberOfBytes, u8 *DataAddress);
//void IIC_ReadData(u8 NumberOfBytes, u8 *DataAddress);

void IIC_WriteData(u8 RegAddr, u16 Data);
u16 IIC_ReadData(u8 RegAddr);


#endif

