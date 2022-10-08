

#ifndef _EEPROM_H_
#define _EEPROM_H_



//------------------------------------------------------------------------------
OS_EXT u16 WriteFlag;
OS_EXT u8 DataLength;

OS_EXT u32 UserTotalSec;
OS_EXT u8 F_BatteryEmpty;
OS_EXT u8 BatteryChargeDischargeCtr;

//------------------------------------------------------------------------------
void WriteDataToEEPROM(void);
void ReadDataForEEPROM(void);


#endif

