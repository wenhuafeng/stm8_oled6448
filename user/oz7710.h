/* ========================================================================== */
/*                                                                            */
/*   o2micro_charger.h                                                      */
/*   (c) 2001 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/* This program is free software; you can redistribute it and/or modify it    */
/* under the terms of the GNU General Public License version 2 as published   */
/* by the Free Software Foundation.											  */
/*																			  */
/* This program is distributed in the hope that it will be useful, but        */
/* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY */
/* or FITNESS FOR A PARTICULAR PURPOSE.										  */
/* See the GNU General Public License for more details.						  */
/*																			  */
/* You should have received a copy of the GNU General Public License along	  */
/* with this program.  If not, see <http://www.gnu.org/licenses/>.			  */
/* ========================================================================== */

#ifndef __OZ7710_H__
#define __OZ7710_H__

#define CHIP_ADDRESS       0x42
#define CELL_NUM           7
#define RSENCE_VALUE       25  // be carefull expand 10 times
#define PARALLEL_R         100 // means temperuature parallel R is 100K
#define OZ7710_TEMPERATURE 0   // whf add

/****************************************************************************
* Struct section
*  add struct #define here if any
***************************************************************************/
typedef struct tag_one_latitude_data {
    u8 x;
    u8 y;
} one_latitude_data_t;

#define TEMPERATURE_DATA_NUM 32

#define REG_NTC_VOLT 0x10

#define REG_CELL_VOLT  0x11
#define CELL_VOLT_STEP 125 / 100 //1.25mv
#define REG_PACK_VOLT  0x1D
#define PACK_VOLT_STEP 125 / 100 //1.25mv
#define REG_CURRENT_1B 0x1B

#define REG_PACKC_SAVE   0x31
#define PACK_CURRENT_LSB 625 / 40000 //0.0625/4

#define REG_MAX_DATA 0x38

#define REG_MIN_DATA 0x39

#define REG_SW_CTRL           0x40
#define TRIGGER_SCAN_REQ_MASK 0x0010

#define REG_BALANCE_STATUS 0x41
#define REG_INTERRUPT      0x42

#define REG_STATUS             0x43
#define TRIGGER_SCAN_FLAG_MASK 0x4000

#define REG_LED_CTRL   0x44
#define REG_EFUSE_MODE 0x50
#define ALLOW_WRT      0x8000
#define EFUSE_MODE     0x0003
#define ALLOW_REGISTER 0x01
#define ALLOW_EFUSE    0x02

//efuse register
#define EFUSE_LEDTH    0x66
#define EFUSE_CFG      0x67
#define EFUSE_OVTH     0x68
#define EFUSE_UVTH     0x69
#define EFUSE_OCTH     0x6A
#define EFUSE_MIXTH    0x6B
#define EFUSE_CUT      0x6C
#define EFUSE_COT      0x6D
#define EFUSE_DOT      0x6E
#define EFUSE_USERFUSE 0x6F

typedef struct oz7710_chip {
    uint16_t cell_volt[CELL_NUM];
    int32_t system_current;
    int16_t temperature;
    uint16_t pack_volt;
    uint16_t which_cell_max;
    uint16_t max_cell_data;
    uint8_t which_cell_min;
    uint16_t min_cell_data;
    uint16_t balance_status;
    uint16_t status;
} o2_chip_t;

//-----------------------------------------------------------------
void oz7710_pc_mode_detect(void);
void oz7710_init(void);
void oz7710_work_fun(void);

#endif //end of #ifndef	__O2MICRO_CHARGER_H
