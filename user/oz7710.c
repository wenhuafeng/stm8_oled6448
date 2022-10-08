/*****************************************************************************
* Copyright(c) O2Micro, 2013. All rights reserved.
*
* O2Micro oz7710 charger driver
* File: oz7710.c

* This program is free software and can be edistributed and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
* This Source Code Reference Design for O2MICRO oz1c105 charger access (\u201cReference Design\u201d)
* is sole for the use of PRODUCT INTEGRATION REFERENCE ONLY, and contains confidential
* and privileged information of O2Micro International Limited. O2Micro shall have no
* liability to any PARTY FOR THE RELIABILITY, SERVICEABILITY FOR THE RESULT OF PRODUCT
* INTEGRATION, or results from: (i) any modification or attempted modification of the
* Reference Design by any party, or (ii) the combination, operation or use of the
* Reference Design with non-O2Micro Reference Design.
*****************************************************************************/

#ifndef  OS_MASTER_FILE
#define  OS_GLOBALS
#include "common.h"
#endif


#if (_OZ7710_)


/*********************************************************/
#define BW_ABS(a,b) ( ((a) > (b)) ? ((a) - (b)) : ((b) - (a)) )

#define RETRY_CNT 5

#if (OZ7710_TEMPERATURE)
code one_latitude_data_t cell_temp_data[TEMPERATURE_DATA_NUM] = {
    {3740,   120}, {4650,   113}, {5820,   105},
    {6730,   100}, {7810,    95}, {9100,    90},
    {10640,   85}, {12490,   80}, {14720,   75},
    {17420,   70}, {20720,   65}, {24760,   60},
    {29730,   55}, {35880,   50}, {43540,   45},
    {53120,   40}, {65190,   35}, {80480,   30},
    {100000,  25}, {125080,  20}, {157530,  15},
    {199870,  10}, {255470,   5}, {329190,   0},
    {427750,  -5}, {560720, -10}, {741830, -15},
    {991020 ,-20}, {1337500,-25},
    {1824600,-30}, {2517410 -35}, {3514950,-40},
};
#endif

o2_chip_t o2_chip;

BOOLEAN F_pc_mode;

/*****************************************************************************
 * Description:
 *		crc8_calc
 * Parameters:
 *		*pdata: point to data buffer which need to calculate
 *		n:      data number
 * Return:
 *      calculate data
 *****************************************************************************/
u8 crc8_calc(u8 *Pdata, u8 n)
{
  u8 crc = 0;
  u8 crcdata;
  u8 i,j;

  for (i=0; i<n; i++)
  {
    crcdata = Pdata[i];
    for (j=0x80; j!=0; j>>=1)
    {
      if ((crc & 0x80) != 0) {
        crc = (crc << 1) ^ 0x07;
      } else {
        crc <<= 1;
      }
      if ((crcdata & j) != 0) {
        crc ^= 0x07;
      }
    }
  }

  return crc;
}

u8 calc_crc_read(u8 slave_addr, u8 reg_addr, u16 Data)
{
  u8 Pdata[5];

  Pdata[0] = slave_addr;
  Pdata[1] = reg_addr;
  Pdata[2] = (slave_addr | 0x01);
  Pdata[3] = (Data >> 8);
  Pdata[4] = (u8)Data;

  return crc8_calc(Pdata, 5);
}

u8 calc_crc_write(u8 slave_addr, u8 reg_addr, u16 Data)
{
  u8 Pdata[4];

  Pdata[0] = slave_addr;
  Pdata[1] = reg_addr;
  Pdata[2] = (Data >> 8);
  Pdata[3] = (u8)Data;

  return crc8_calc(Pdata, 4);
}


/*****************************************************************************
 * Description:
 *		o2m_read_word
 * Parameters:
 *		index:	register index to be read
 *		*dat:	buffer to store data read back
 * Return:
 *      negative errno else a data byte received from the device.
 *****************************************************************************/
u8 o2m_read_word(u8 index, u16 *dat)
{
  u8 ret = HAL_ERROR;
  u8 i;
  u8  readdata_low;
  u8  CRC8;
  u16 readdata_high;

  for (i=0; i < RETRY_CNT; i++) {
    IIC_Start();
    IIC_SendByte(IICSENB0Address + Write);
    if (IIC_Ack() == 0) {
      IIC_SendByte(index);
      if (IIC_Ack() == 0) {
        IIC_Start();
        IIC_SendByte(IICSENB0Address + Read);
        if (IIC_Ack() == 0) {
          DelayUs(250);
          DelayUs(250);
          readdata_high = IIC_ReceiveByte(1);
          readdata_low = IIC_ReceiveByte(1);
          CRC8 = IIC_ReceiveByte(0);
          IIC_Stop();
          ret = HAL_OK;
          break;
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

  *dat = (readdata_high << 8);
  *dat |= readdata_low;
  if (CRC8 != calc_crc_read(CHIP_ADDRESS, index, *dat)) {
    ret = HAL_ERROR;
  } else {
    ret = HAL_OK;
  }

  return ret;
}

/*****************************************************************************
 * Description:
 *		o2m_write_word
 * Parameters:
 *		index:	register index to be write
 *		data:		write data
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 o2m_write_word(u8 index, u16 Data)
{
  u8 ret = HAL_ERROR;
  u8 i;
  u8 dat[3];

  dat[0] = Data >> 8;
  dat[1] = (u8)Data;
  dat[2] = calc_crc_write(CHIP_ADDRESS, index, Data);

  for (i=0; i<RETRY_CNT; i++) {
    IIC_Start();
    IIC_SendByte(IICSENB0Address + Write);
    if (IIC_Ack() == 0) {
      IIC_SendByte(index);
      if (IIC_Ack() == 0) {
        IIC_SendByte(dat[0]);
        if (IIC_Ack() == 0) {
          IIC_SendByte(dat[1]);
          if (IIC_Ack() == 0) {
            IIC_SendByte(dat[2]);
            IIC_Ack();
            IIC_Stop();
            ret = HAL_OK;
            break;
          }
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

  return ret;
}


u8 oz7710_update_bits(u8 reg, u16 mask, u16 Data)
{
  u8 ret;
  u16 tmp;

  ret = o2m_read_word(reg, &tmp);
  if (ret != HAL_OK)
    return ret;

  if ((tmp & mask) != Data) {
    tmp &= ~mask;
    tmp |= Data & mask;
    return o2m_write_word(reg, tmp);
  } else {
    return HAL_OK;
  }
}

/*****************************************************************************
 * Description:
 *		oz7710_read_cell_volt
 * Parameters:
 *		cell_channel: which cell ,from 0 to 10
 *      volt: cell voltage buffer
 * Return:
 *      negative errno, zero or positive on success.
 *****************************************************************************/
u8 oz7710_read_cell_volt(u8 cell_channel,u16 *volt)
{
  u16 Data;
  u8 ret;

  ret =  o2m_read_word(REG_CELL_VOLT + cell_channel,&Data);
  //if(cell_channel == 0)
  //    printf("cell channel 0 register data is %d \n",Data);
  //if(ret <0)
  //    printf("read cell voltage crc error %d\n",cell_channel);
  Data = (Data & 0x0fff) * CELL_VOLT_STEP;
  *volt = (u16)Data;

  return ret;
}

/*****************************************************************************
 * Description:
 *		oz7710_read_pack_volt
 * Parameters:
 *      volt: voltage buffer
 * Return:
 *      negative errno, zero or positive on success.
 *****************************************************************************/
u8 oz7710_read_pack_volt(u16 *volt)
{
  u16 Data;
  u8 ret;
  u8 i;

  ret =  o2m_read_word(REG_PACK_VOLT, &Data);
  Data = (Data & 0x0fff) * PACK_VOLT_STEP ;
  *volt = Data;

  o2_chip.pack_volt = 0;
  for(i=0; i<CELL_NUM; i++)
  {
    o2_chip.pack_volt += o2_chip.cell_volt[i];
  }

  return ret;
}

/*****************************************************************************
 * Description:
 *		oz7710_read_max_volt_cell
 * Parameters:
 *	    cell_num: cell number buffer
 *	    volt: max voltage buffer
 * Return:
 *      negative errno, zero or positive on success.
 *****************************************************************************/
/*
u8 oz7710_read_max_volt_cell(u8 *cell_num, u16 *volt)
{
  u16 Data;
  u8 ret;

  ret =  o2m_read_word(REG_MAX_DATA, &Data);
  *volt  = (Data & 0x0fff) * PACK_VOLT_STEP;
  *cell_num = (u8)(Data >> 12);

  //printk("max is %x\n",data);
  return ret;
}*/

/*****************************************************************************
 * Description:
 *		oz7710_read_min_volt_cell
 * Parameters:
 *	    cell_num: which cell voltage min number
 *	    volt: voltage buffer
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
 /*
u8 oz7710_read_min_volt_cell(u8 *cell_num,u16 *volt)
{
  u16 Data;
  u8 ret;

  ret =  o2m_read_word(REG_MIN_DATA, &Data);
  *volt = (Data & 0x0fff) * PACK_VOLT_STEP ;
  *cell_num  = (u8)(Data >> 12);
  //printk("min is %x\n",data);

  return ret;
}*/

/*****************************************************************************
 * Description:
 *		oz7710_read_op_config
 * Parameters:
 *	    index:	which efuse op  config need to read
 *	    data: read data buffer
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 oz7710_read_op_config(u8 index,u16 *Data)
{
  u8 ret;

  if ((index < 0x76) || (index > 0x7f))
      return HAL_ERROR;

  ret =  o2m_read_word(index, Data);

  return ret;
}

/*****************************************************************************
 * Description:
 *		oz7710_write_op_config
 * Parameters:
 *		index: which efuse op config need to write
 *		datum: data need to be write
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 oz7710_write_op_config(u8 index,u16 datum)
{
  u8 ret;

  if ((index < 0x76) || (index > 0x7f))
    return HAL_ERROR;

  ret = oz7710_update_bits(REG_EFUSE_MODE,ALLOW_WRT,1<<15);
  if (ret != HAL_OK)
    return ret;

  ret =  oz7710_update_bits(REG_EFUSE_MODE,EFUSE_MODE,ALLOW_REGISTER);
  if (ret != HAL_OK)
    return ret;

  ret = o2m_write_word(index,datum);

  oz7710_update_bits(REG_EFUSE_MODE,EFUSE_MODE,0x00);

  ret = oz7710_update_bits(REG_EFUSE_MODE,ALLOW_WRT,0 << 15);

  return ret;
}

/*****************************************************************************
 * Description:
 *		oz7710_update_op_config
 * Parameters:
 *		index: which efuse op config need to write
 *		datum: data need to be write
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 oz7710_update_op_config(u8 index,u16 mask,u16 datum)
{
  u8 ret;

  if ((index < 0x76) || (index > 0x7f))
    return HAL_ERROR;

  ret = oz7710_update_bits(REG_EFUSE_MODE,ALLOW_WRT,1<<15);
  if (ret != HAL_OK)
    return ret;

  ret =  oz7710_update_bits(REG_EFUSE_MODE,EFUSE_MODE,ALLOW_REGISTER);
  if (ret != HAL_OK)
    return ret;

  ret =  oz7710_update_bits(index,mask,datum);

  oz7710_update_bits(REG_EFUSE_MODE,EFUSE_MODE,0x00);

  ret = oz7710_update_bits(REG_EFUSE_MODE,ALLOW_WRT,0 << 15);

  return ret;
}

/*****************************************************************************
 * Description:
 *		oz7710_read_current
 * Parameters:
 *	    current_data:  read current buffer
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 oz7710_read_current(u32 *current_data)
{
  u16 Data;
  u8 ret;
  u8 wait_count = 0;

  //clear trigger scan flag
  o2m_write_word(REG_STATUS,TRIGGER_SCAN_FLAG_MASK);

  //request trigger scan
  ret =  oz7710_update_bits(REG_SW_CTRL,TRIGGER_SCAN_REQ_MASK,1<<4);
  if (ret != HAL_OK)
    return ret;

  //wait trigger scan flag
  do {
      ret =  o2m_read_word(REG_STATUS,&Data);
      if (Data & TRIGGER_SCAN_FLAG_MASK)
          break;
      DelayMs(5);
  } while (wait_count++ < 10);

  if ((ret != HAL_OK) || !(Data & TRIGGER_SCAN_FLAG_MASK)) {
      //printk("trigger sacn flag is error  %x \n",data);
      return ret;
  }
  wait_count = 0;

  // read current data
  do {
      ret =  o2m_read_word(REG_PACKC_SAVE,&Data);

      if (ret == HAL_OK)
          break;
      DelayMs(5);
  } while (wait_count++ < 10);
  if (ret != HAL_OK) {
      //printk(" read current data error  %x \n",data);
      return ret;
  }

  *current_data =  (u32)(u16)Data*10000*PACK_CURRENT_LSB/RSENCE_VALUE;
  *current_data *= -1;

  return ret;
}

/*****************************************************************************
 * Description:
 *		oz7710_read_current_1b
 * Parameters:
 *	    current_data:  read current buffer
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 oz7710_read_current_1b(u32 *current_data)
{
  u16 Data;
  u8 ret;

  ret =  o2m_read_word(REG_CURRENT_1B,&Data);

  if (ret != HAL_OK) {
      //printk(" read current data 1b error  %x \n",data);
      return ret;
  }

  *current_data =  (u32)(u16)Data*10000*PACK_CURRENT_LSB/RSENCE_VALUE;
  *current_data *= -1;

  return ret;
}


/*****************************************************************************
 * Description:
 *		oz7710_read_status
 * Parameters:
 *	    status: read staus buffer
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 oz7710_read_status(u16 *status)
{
  u8 ret;
  //u32 Data;
  //u8 wait_count = 0;

  ret =  o2m_read_word(REG_STATUS,status);

  return ret;
}

#if (OZ7710_TEMPERATURE)
/*****************************************************************************
* Description:
*		one_latitude_table
* Parameters:
*	    number: number of the temperature data array
*	    data: data buffer
*	    value: x data in the array
* Return:
*	    what does this function returned?
*****************************************************************************/
static u8 one_latitude_table(u8 number, one_latitude_data_t *Data, u32 value)
{
  u8 j;
  u8 res;

  for (j=0; j<number; j++)
  {
    if (Data[j].x ==value) {
      res = Data[j].y;
      return res;
    }
    if (Data[j].x > value)
      break;
  }

  if (j == 0) {
    res = Data[j].y;
  }
  else if (j == number) {
    res = Data[j -1].y;
  }
  else {
    res = ((value - Data[j -1].x) * (Data[j].y - Data[j -1].y));

    if((Data[j].x - Data[j -1].x) != 0)
      res = res / (Data[j].x  - Data[j-1].x );
    res += Data[j-1].y;
  }

  return res;
}

/*****************************************************************************
 * Description:
 *		oz7710_read_temperature
 * Parameters:
 *	    temperature: temperature data buffer
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 oz7710_read_temperature(u32 *temperature)
{
  u16 Data;
  u8 ret;

  ret =  o2m_read_word(REG_NTC_VOLT,&Data);
  Data = (Data & 0x0fff) * 625 / 1000;
  Data = (1000 * Data * PARALLEL_R) / (2000 - Data);
  //printf("temp data:%d\n",Data);
  *temperature = one_latitude_table(TEMPERATURE_DATA_NUM,cell_temp_data,Data);

  return ret;
}
#endif

#define     DISABLE_CELL_BALANCE            0x00
#define     BALANCE_IN_IDLE_CHARGE_STATE    0x01
#define     BALANCE_IN_IDLE_STATE           0x02
#define     BALANCE_IN_CHARGE_STATE         0x03
/*****************************************************************************
 * Description:
 *		oz7710_enable_balance
 * Parameters:
 *	 uint8_t cb_option
 *	            00:disable Cell Balance (CB) function;
 *	            01:do balance in idle-state or in charge-state;
 *	            10:do balance just in idle-state;
 *	            11:do balance just in charge-state.
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 oz7710_balance_function(uint8_t cb_option)
{
  u8 ret;
  ret =  oz7710_update_op_config(0x7d,0x6000,cb_option<<13);
  return ret;
}

/*****************************************************************************
 * Description:
 *		oz7710_read_balance_status
 * Parameters:
 *	    status: read staus buffer
 * Return:
 *      negative errno, zero on success.
 *****************************************************************************/
u8 oz7710_read_balance_status(u16 *status)
{
  u8 ret;
  //u32 Data;
  //u8 wait_count = 0;

  ret =  o2m_read_word(REG_BALANCE_STATUS,status);

  return ret;
}

void oz7710_pc_mode_detect(void)
{
  u8 Port;

  Port = P3;
  if ((Port & 0x01) == 0x00) {
    F_pc_mode = 1;
    SCLIN();
    SDAIN();
  } else {
    if (F_pc_mode) {
      F_pc_mode = 0;
      SCLOUT();
      SDAOUT();
      oz7710_init();
      DelayMs(10);
    }
  }
}

void oz7710_init(void)
{
  u16 Data;

  // this is a sample to read and write op efuse config
  oz7710_read_op_config(0x76,&Data);
  //printk("1st read op data is %d \n",Data);
  //oz7710_write_op_config(0x76,0x00);
  //oz7710_read_op_config(0x76,&data);
  //printk("second read op data is %d \n",data);
  oz7710_update_op_config(0x76,0x0700,0x3<<8);
  oz7710_read_op_config(0x76,&Data);
  //printk("second read op data is %x \n",Data);

  //this is a sample to enable balance function
  oz7710_read_op_config(0x7d,&Data);
  //printk("1st read op data 0x7d is %d \n",Data);
  oz7710_balance_function(BALANCE_IN_IDLE_CHARGE_STATE);
  oz7710_read_op_config(0x7d,&Data);
  //printk("second read op data 0x7d is %x \n",Data);
}

void oz7710_work_fun(void)
{
  u8 ret;
  u16 Data;
  u8 i;
//  u8 num;
//  static  uint8_t test;
  u16 cell_volt;
  u32 current_data;
  static u32 test_times;
#if (OZ7710_TEMPERATURE)
  u32 temperature;
#endif

  if (F_pc_mode) return;

  ret =  o2m_read_word(0x00, &Data);
  //printf("read chip is data = %x \n",Data);

  for(i=0; i<CELL_NUM; i++)
  {
     ret = oz7710_read_cell_volt(i, &cell_volt);
     if (ret == HAL_OK) {
       o2_chip.cell_volt[i] = cell_volt;
     }
  }

  ret =  oz7710_read_pack_volt(&Data);
  if (ret == HAL_OK)
    o2_chip.pack_volt = Data;

  /*
  ret = oz7710_read_max_volt_cell(&num, &cell_volt);
  if (ret == HAL_OK) {
    o2_chip.max_cell_data = cell_volt;
    o2_chip.which_cell_max = num;
  }

  ret = oz7710_read_min_volt_cell(&num, &cell_volt);
  if (ret == HAL_OK) {
    o2_chip.min_cell_data = cell_volt;
    o2_chip.which_cell_min = num;
  }
  */

  ret = oz7710_read_current(&current_data);
  if (ret == HAL_OK)
    o2_chip.system_current = current_data;

  ret = oz7710_read_status(&Data);
  if (ret == HAL_OK)
    o2_chip.status = Data;

  //this is a sample to read balance status,which cell is in balance
  ret = oz7710_read_balance_status(&Data);
  if (ret == HAL_OK)
    o2_chip.balance_status = Data;

  //printf("## OZ7710 information test times is %d ##\n",test_times);
  test_times++;

  oz7710_read_current_1b(&current_data);
  //printf("current data 1b is %d\n",current_data);

#if (OZ7710_TEMPERATURE)
  oz7710_read_temperature(&temperature);
  if (ret == HAL_OK)
    o2_chip.temperature = temperature;
#endif

  //print_all_charger_info();
  //schedule_delayed_work(&oz7710_work, msecs_to_jiffies(2000));
  //DelayMs(200);
  //printf("oz7710_work");
}

#endif

