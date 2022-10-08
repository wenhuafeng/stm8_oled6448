#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

#if (_EEPROM_FUNC_)

#define EEPROM_STARTADDR 0x1000
#define _WRITE_FLAG_     0x3A8F

union b_f {
    u16 buffer[64];
    struct {
        u8 buff[64 * 2];
    } WRITE;
};

//------------------------------------------------------------------------------
void EEPROM_WriteByte(u8 Addr, u8 Data)
{
    u8 *Ptr_SegAddr;

    Ptr_SegAddr = (u8 *)(EEPROM_STARTADDR + Addr);
    FLASH->PUKR = 0xAE;
    FLASH->PUKR = 0x56;
    while (!(FLASH->IAPSR & FLASH_IAPSR_DUL))
        ;
    asm("sim");
    *Ptr_SegAddr = Data;
    while (!(FLASH->IAPSR & FLASH_IAPSR_EOP))
        ;
    asm("rim");
    FLASH->IAPSR &= ~FLASH_IAPSR_DUL;
}

//------------------------------------------------------------------------------
u8 EEPROM_ReadByte(u8 Addr)
{
    u16 Data = 0;
    u8 *Ptr_SegAddr;

    Ptr_SegAddr = (u8 *)(EEPROM_STARTADDR + Addr);
    Data        = *Ptr_SegAddr;

    return Data;
}

//------------------------------------------------------------------------------
void EEPROM_WriteXByte(u8 Addr, u8 *Data, u8 dataCount)
{
    do {
        EEPROM_WriteByte(Addr, *Data++);
    } while (--dataCount);
}

//------------------------------------------------------------------------------
void EEPROM_ReadXByte(u8 addr, u8 *Data, u8 dataCount)
{
    while (dataCount--) {
        *Data++ = EEPROM_ReadByte(addr++);
    }
}

//------------------------------------------------------------------------------
void WriteDataToEEPROM(void)
{
    union b_f buf;

    u8 i, j;
    u16 Total = 0x00;

    //buf.buffer[0],buf.buffer[1],buf.buffer[2] there no use.
    i = 3;

    //16 bit
    //**********lamp *******************************************
    buf.buffer[i++] = (UserTotalSec >> 16);
    buf.buffer[i++] = UserTotalSec;
    //**********xxxx *******************************************

    //8 bit
    j                   = i * 2;
    buf.WRITE.buff[j++] = (F_BatteryEmpty);
    buf.WRITE.buff[j++] = (BatteryChargeDischargeCtr);

    //  //**********¡Ó¢G¡¦aDIM*************************************
    //  buf.WRITE.buff[j++] = DIM.min_start;
    //  buf.WRITE.buff[j++] = DIM.hour_start;
    //  buf.WRITE.buff[j++] = DIM.min_stop;
    //  buf.WRITE.buff[j++] = DIM.hour_stop;
    //  buf.WRITE.buff[j++] = DIM.dim_switch;
    //  //**********¡Ó¢G¡¦aD!E¡ÓOAE?*************************************
    //  buf.WRITE.buff[j++] = F_HR;
    //  buf.WRITE.buff[j++] = flag_DM_MD;
    //  //**********¡Ó¢G¡¦aALARM1*************************************
    //  buf.WRITE.buff[j++] = alarm[0].min;
    //  buf.WRITE.buff[j++] = alarm[0].hour;
    //  buf.WRITE.buff[j++] = alarm[0].mode;
    //  buf.WRITE.buff[j++] = alarm[0].dayselet;
    //  buf.WRITE.buff[j++] = alarm[0].snooze;
    //  buf.WRITE.buff[j++] = alarm[0].vol;
    //  buf.WRITE.buff[j++] = alarm[0].al_on_off;
    //  buf.WRITE.buff[j++] = alarm[0].wakeup_lamp_level;
    //  //**********¡Ó¢G¡¦aALARM2*************************************
    //  buf.WRITE.buff[j++] = alarm[1].min;
    //  buf.WRITE.buff[j++] = alarm[1].hour;
    //  buf.WRITE.buff[j++] = alarm[1].mode;
    //  buf.WRITE.buff[j++] = alarm[1].dayselet;
    //  buf.WRITE.buff[j++] = alarm[1].snooze;
    //  buf.WRITE.buff[j++] = alarm[1].vol;
    //  buf.WRITE.buff[j++] = alarm[1].al_on_off;
    //  buf.WRITE.buff[j++] = alarm[1].wakeup_lamp_level;

    //buf.buffer[0],buf.buffer[1],buf.buffer[2]  no checksum Calculation.
    DataLength = j;
    for (i = 6; i < DataLength; i++) {
        Total += buf.WRITE.buff[i];
    }
    buf.buffer[0] = Total; //save checksum to "0x00,0x01 Byte".
    buf.buffer[1] = DataLength;
    buf.buffer[2] = _WRITE_FLAG_;

    EEPROM_WriteXByte(0x00, &buf.WRITE.buff[0x00], 16);
    EEPROM_WriteXByte(0x10, &buf.WRITE.buff[0x00], 16);
    EEPROM_WriteXByte(0x20, &buf.WRITE.buff[0x00], 16);
    EEPROM_WriteXByte(0x30, &buf.WRITE.buff[0x00], 16);
    EEPROM_WriteXByte(0x40, &buf.WRITE.buff[0x00], 16);
    EEPROM_WriteXByte(0x50, &buf.WRITE.buff[0x00], 16);
    EEPROM_WriteXByte(0x60, &buf.WRITE.buff[0x00], 16);
}

//------------------------------------------------------------------------------
void ReadDataForEEPROM(void)
{
    union b_f buf;

    u8 i, j;
    u16 Total = 0x00;

    EEPROM_ReadXByte(0x00, &buf.WRITE.buff[0], 128);
    DataLength = buf.buffer[1];

    if (buf.buffer[2] == _WRITE_FLAG_) {
        for (i = 6; i < DataLength; i++) { //buf.buffer[0],buf.buffer[1],no checksum Calculation.
            Total += buf.WRITE.buff[i];
        }

        if ((Total == buf.buffer[0]) && (Total != 0x00)) {
            //checksum data OK.
            WriteFlag = buf.buffer[2];

            i            = 3;
            UserTotalSec = buf.buffer[i++];
            UserTotalSec <<= 16;
            UserTotalSec |= buf.buffer[i++];

            j                         = i * 2;
            F_BatteryEmpty            = buf.WRITE.buff[j++];
            BatteryChargeDischargeCtr = buf.WRITE.buff[j++];
        }
    }
}

//------------------------------------------------------------------------------
void ClrDataEEPROM(void)
{
    u8 Tbl[16] = { 0 };

    EEPROM_WriteXByte(0x00, &Tbl[0x00], 16);
    EEPROM_WriteXByte(0x10, &Tbl[0x00], 16);
    EEPROM_WriteXByte(0x20, &Tbl[0x00], 16);
    EEPROM_WriteXByte(0x30, &Tbl[0x00], 16);
    EEPROM_WriteXByte(0x40, &Tbl[0x00], 16);
    EEPROM_WriteXByte(0x50, &Tbl[0x00], 16);
    EEPROM_WriteXByte(0x60, &Tbl[0x00], 16);
}

#endif
