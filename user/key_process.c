#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

//---------------------------------------
//Key function
//Keys
enum {
    _NO_KEY_,
    _KEY_1_,
    _KEY_2_,
    _MAX_KEY_,
};

//P17
//#define _ALL_KEY_MASK_1_           0x08
//#define _ALL_KEY_MASK_RETURN_1_    (~0x08)
//#define _KEY_PORT_1_               P3

//P35
//#define _ALL_KEY_MASK_2_           0x20
//#define _ALL_KEY_MASK_RETURN_2_    0xdf
//#define _KEY_PORT_2_               P3

//ALL key
#define _ALL_KEY_MASK_ 0x08

#define _HOLD_TIMER_KEY_ 4
uint8_t HoldKeyCtr;

FlagStatus F_Key;
FlagStatus F_PushKey;
FlagStatus F_NewKey;
FlagStatus F_HoldKey;
FlagStatus F_TwoKey;
uint8_t Key;
uint8_t OldKey;

void ScanKey(void)
{
    //uint8_t i,j;
    //uint8_t l;

    //l = _KEY_PORT_2_;
    //l = (l & _ALL_KEY_MASK_2_);
    //l = 0;
    //i = _KEY_PORT_1_;
    //i = (i & _ALL_KEY_MASK_1_);
    //i = i|l;

    //if (i == _ALL_KEY_MASK_) {
    //  F_PushKey = 0;
    //  F_NewKey    = 0;
    //  F_HoldKey   = 0;
    //  F_TwoKey    = 0;
    //  goto normal_quit_scan_key;
    //}

    if (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN)) {
        F_PushKey = RESET;
        F_NewKey  = RESET;
        F_HoldKey = RESET;
        F_TwoKey  = RESET;
        goto normal_quit_scan_key;
    }

    DelayMs(2);

    //l = _KEY_PORT_2_;
    //l = (l & _ALL_KEY_MASK_2_);
    //l = 0;
    //j = _KEY_PORT_1_;
    //j = (j & _ALL_KEY_MASK_1_);
    //j = j|l;

    if (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN)) {
        F_PushKey = RESET;
        F_NewKey  = RESET;
        F_HoldKey = RESET;
        F_TwoKey  = RESET;
        goto normal_quit_scan_key;
    }

    /*
  if (i == j) {
    if ((i & _ALL_KEY_MASK_1_) == 0x00) {
      //push key1
      Key = _KEY_1_;
    }
    //else if ((i & _ALL_KEY_MASK_2_) == 0x00) {
    //  //push key2
    //  Key = _KEY_2_;
    //}
    else {
      //release key
      Key = _NO_KEY_;
    }
  } else {
    //error
    Key = _NO_KEY_;
  }*/

    Key = _KEY_1_;
    if (Key == _NO_KEY_) {
        //Key   = _NO_KEY_;
        //F_PushKey = 0;
        F_NewKey  = RESET;
        F_HoldKey = RESET;
        F_TwoKey  = RESET;
        goto normal_quit_scan_key;
    } else {
        if (F_PushKey == RESET) {
            OldKey    = Key;
            F_NewKey  = SET;
            F_PushKey = SET;
            //TEST
            //P10 = 1;
        }
    }

normal_quit_scan_key:
    asm("nop");
}

FlagStatus HoldKeyCom(void)
{
    if (F_NewKey == SET) {
        HoldKeyCtr = 0;
    } else {
        if (F_HoldKey == RESET) {
            if (HoldKeyCtr == _HOLD_TIMER_KEY_) {
                F_HoldKey = SET;
                return SET;
            }
        }
    }

    return RESET;
}

static void PushKeyFunc(void)
{
    switch (Key) {
        case _KEY_1_:
            if (HoldKeyCom()) {
            } else {
                if (F_NewKey == 1) {
                    VentDelay = 0x00;
                    F_Vent = SET;
                }
            }
            break;
        case _KEY_2_:
            if (HoldKeyCom()) {
                //P3_4 = 0;
                //OldKey = 0x00;
            }
            break;
        default:
            break;
    }

    F_NewKey = RESET;
}

static void ReleKeyFunc(void)
{
    uint8_t tmp;

    tmp    = OldKey;
    OldKey = 0x00;

    switch (tmp) {
        case _KEY_1_:
            VentDelay     = _VENT_DELAY_; //(500/10);//0.5S
            F_WaterPumpOn = RESET;
            break;
        case _KEY_2_:
            //if (SettingCom()) {
            //if (F_NewKey) {
            //GRENN_LED = 0;
            OldKey = 0x00;
            //}
            //}
            break;
        default:
            break;
    }

    OldKey = 0x00;
}

void KEY_Process(void)
{
    if (F_PushKey) {
        if ((Key < _MAX_KEY_) && (Key != _NO_KEY_)) {
            PushKeyFunc();
        }
    } else {
        if ((OldKey < _MAX_KEY_) && (OldKey != _NO_KEY_)) {
            ReleKeyFunc();
        }
    }
}

void TempHeatControl(int16_t Temp)
{
    if (F_PushKey == SET) {
        if (Temp < 1200) {
            HeatSpeed = 0;
        } else if (Temp < 1300) {
            HeatSpeed = 0;
        } else if (Temp < 1400) {
            HeatSpeed = 0;
        }

        if (Temp > 1000) {
            F_WaterPumpOn = SET;
        } else {
            F_WaterPumpOn = RESET;
        }

        if (F_Heat == SET) {
            if (Temp > 1500) {
                F_Heat = RESET;
            }
        } else {
            //if (F_PushKey == SET) {
            if (F_Heat == RESET) {
                if (Temp < 1400) {
                    F_Heat = SET;
                }
            }
            //}
        }
    } else {
        if (Temp < 1000) {
            HeatSpeed = 0;
        } else if (Temp < 1100) {
            HeatSpeed = 2;
        } else if (Temp < 1200) {
            HeatSpeed = 4;
        } else {
            HeatSpeed = 4;
        }

        if (F_Heat == SET) {
            if (Temp > 1200) {
                F_Heat = RESET;
            }
        } else {
            //if (F_PushKey == SET) {
            if (F_Heat == RESET) {
                if (Temp < 1100) {
                    F_Heat = SET;
                }
            }
            //}
        }
    }
}
