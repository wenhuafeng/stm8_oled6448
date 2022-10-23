#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "includes.h"
#endif

enum {
    _NO_KEY_,
    _KEY_1_,
    _KEY_2_,
    _MAX_KEY_,
};

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

#define _TIME_BASE_xMS_ (10)
#define _VENT_DELAY_ (1000 / _TIME_BASE_xMS_)

void ScanKey(void)
{
    if (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN)) {
        F_PushKey = RESET;
        F_NewKey  = RESET;
        F_HoldKey = RESET;
        F_TwoKey  = RESET;
        goto normal_quit_scan_key;
    }

    DelayMs(11);

    if (GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN)) {
        F_PushKey = RESET;
        F_NewKey  = RESET;
        F_HoldKey = RESET;
        F_TwoKey  = RESET;
        goto normal_quit_scan_key;
    }

    Key = _KEY_1_;
    if (Key == _NO_KEY_) {
        F_NewKey  = RESET;
        F_HoldKey = RESET;
        F_TwoKey  = RESET;
        goto normal_quit_scan_key;
    } else {
        if (F_PushKey == RESET) {
            OldKey    = Key;
            F_NewKey  = SET;
            F_PushKey = SET;
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
                    COMMON_SetVentDelay(0x00);
                }
            }
            break;
        case _KEY_2_:
            if (HoldKeyCom()) {
                ;
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
            COMMON_SetVentDelay(_VENT_DELAY_);
            COMMON_SetWaterPumpOnFlag(RESET);
            break;
        case _KEY_2_:
            OldKey = 0x00;
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

void TempHeatControl(int16_t temp)
{
    if (F_PushKey == SET) {
        if (temp < 1200) {
            COMMON_SetHeatSpeed(0);
        } else if (temp < 1300) {
            COMMON_SetHeatSpeed(0);
        } else if (temp < 1400) {
            COMMON_SetHeatSpeed(0);
        }

        if (temp > 1000) {
            COMMON_SetWaterPumpOnFlag(SET);
        } else {
            COMMON_SetWaterPumpOnFlag(RESET);
        }
        COMMON_PushKeyHeat(temp);
    } else {
        if (temp < 1000) {
            COMMON_SetHeatSpeed(0);
        } else if (temp < 1100) {
            COMMON_SetHeatSpeed(2);
        } else if (temp < 1200) {
            COMMON_SetHeatSpeed(4);
        } else {
            COMMON_SetHeatSpeed(4);
        }
        COMMON_ReleKeyHeat(temp);
    }
}
