#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "common.h"
#endif

/********************************************************************/ /**
 * @brief:			Func key release function
 *
 * @param[in]:		NONE
 *
 * @return: 		NONE
 *********************************************************************/
#define ADC_READ_NUM 8

#define K1_V 0 //=AD_Value/3*2 + Prev_ADC_value
#define K2_V 26
#define K3_V 63
#define K4_V 110
#define K5_V 152
#define K6_V 206
//#define	K7_V	212
//#define	K8_V	212

typedef union {
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } bits;
} KeyBits;

KeyBits KeyFlag;
//KeyBits KeyFlag = {0x00};

#define flag_key1_pressed KeyFlag.bits.b0
#define flag_key1_release KeyFlag.bits.b1
#define flag_key1_on      KeyFlag.bits.b2
#define LongPress         KeyFlag.bits.b3
#define LongOnce          KeyFlag.bits.b4
#define Key_witch         KeyFlag.bits.b5

INT8U KeyNumber @0x100; //Force its address to be 0x100
INT8U Time10Ms_keyLongPress;
INT16U ADC_key1_count;

extern INT8U Version[3];

INT8U code Key_Tab1[][2] = {
    { K1, K1_V },
    { K2, K2_V },
    { K3, K3_V },
    { K4, K4_V },
    { K5, K5_V },
    { K6, K6_V },
    //{K7,K7_V},
    //{K8,K8_V},
    { 0, 250 },
};

INT8U code Key_Tab2[][2] = {
    { K9, K1_V },
    { K10, K2_V },
    { K11, K3_V },
    { K12, K4_V },
    { K13, K5_V },
    { K14, K6_V },
    //{K15,K7_V},
    //{K16,K8_V},
    { 0, 250 },
};

/*
void KeyADC_Init(void)
{
  ADCCRH = 0X01; //f=Fx/2
}
*/

INT8U GetKey(INT8U ch, INT8U ad_value)
{
    INT8U i;

    if (ch == 0) {
        for (i = ((sizeof(Key_Tab1) - 2) / 2); i != 0xff; i--) {
            if (i != 0x00) {
                if (ad_value > Key_Tab1[i][1]) {
                    return Key_Tab1[i][0];
                }
            } else {
                return Key_Tab1[0][0];
            }
        }
    } else {
        for (i = ((sizeof(Key_Tab2) - 2) / 2); i != 0xff; i--) {
            if (i != 0x00) {
                if (ad_value > Key_Tab2[i][1]) {
                    return Key_Tab2[i][0];
                }
            } else {
                return Key_Tab2[0][0];
            }
        }
    }

    return 0;
}

INT8U ADCChannelGet(INT8U ch)
{
    INT8U vlu;

    //ADCCRH = 0x02;
    //ADCCRL &= 0x80;
    //ADCCRL |= ch;
    //ADCCRL |= ADC_START;
    //while(!(ADCCRL & ADC_CONVERSION_FINISHED));
    //vlu = ADCDRH;

    return (vlu);
}

void KeyProcess(void)
{
    INT8U AD_Value;
    static INT8U AD_val_1;
    static INT8U KK_1_;

    static INT8U LongPress_Key;
    INT8U i;
    INT16U Total;
    //static INT8U ADC_ValueMax_1,ADC_ValueMin_1;//TEST
    //static INT8U ADC_ValueMax_2,ADC_ValueMin_2;//TEST

    KeyNumber = 0x00;
    i         = ADC_READ_NUM;
    Total     = 0;
    while (i--) {
        //Total += ADCChannelGet(ADC_CH5);
    }
    AD_Value = Total / ADC_READ_NUM;

    if (AD_Value < 250) {
        if (((AD_Value > AD_val_1) ? (AD_Value - AD_val_1) : (AD_val_1 - AD_Value)) < 3) {
            ADC_key1_count++;
            //if ((ADC_ValueMax_1 - ADC_ValueMin_1) > 2) {//TEST
            //    ADC_key1_count = 0x00;
            //}
        } else {
            ADC_key1_count = 0x00;
        }
        AD_val_1 = AD_Value;
        if (ADC_key1_count >= 50) {
            if (flag_key1_release) {
                flag_key1_release = 0;
                KK_1_             = GetKey(0, AD_Value);
            }
            flag_key1_pressed = 1;
        }

        //if (AD_Value > ADC_ValueMax_1) {//TEST
        //    ADC_ValueMax_1 = AD_Value;
        //}
        //else if (AD_Value < ADC_ValueMin_1) {
        //    ADC_ValueMin_1 = AD_Value;
        //}
    } else {
        ADC_key1_count    = 0;
        flag_key1_pressed = 0;
        flag_key1_release = 1;
        //ADC_ValueMax_1 = 0x00;//TEST
        //ADC_ValueMin_1 = 0x00;
    }
    if (flag_key1_pressed) {
        flag_key1_on = 1;
        if (ADC_key1_count > _KEY_MAX_COUNT_) {
            ADC_key1_count = 0;
            LongPress      = 1;
            KeyNumber      = KK_1_ | KEY_TIME_LONG;
        }
    } else if (flag_key1_on) {
        flag_key1_on = 0;
        if (LongPress == 0) {
            KeyNumber = KK_1_;
        } else {
            LongPress = 0;
        }
    }

    if (LongPress) {
        if (Key_witch == 0) {
            Key_witch             = 1;
            Time10Ms_keyLongPress = _KEY_LONG_PRESS_TIME_;
            LongPress_Key         = KeyNumber;
        } else {
            KeyNumber = 0;
            if (Time10Ms_keyLongPress == 0) {
                Time10Ms_keyLongPress = _KEY_LONG_PRESS_TIME_;
                KeyNumber             = LongPress_Key;
            }
        }
    } else {
        Key_witch = 0;
    }

    //VersionView();
}

/********************************************************************/ /**
 * @brief:			xxxx
 *
 * @param[in]:		NONE
 *
 * @return: 		NONE
 *********************************************************************/
/*
void VersionView()
{
	static INT16U V_num = 0;

	if (POWER_ON == 0) {
		if (KeyNumber == MODE_KEY_L) {
			V_num ++;
			if (V_num > 0x5161) {
				V_num = 0;
				ClearLCD();
				dat[1] = 'V' - 'A' + 10;
				dat[2] = Version[0] - '0';
				dat[3] = 38;
				dat[4] = Version[2] - '0';
				dat[5] = Version[3] - '0';
				DataDisplay();
				McuWriteDataToLcd(0,&SEG1,26);
				DelayMs(5000);
			}
		} else {
			V_num = 0;
		}
	} else {
		V_num = 0;
	}
}*/

/********************************************************************/ /**
 * @brief:			xxxx
 *
 * @param[in]:		NONE
 *
 * @return: 		NONE
 *********************************************************************/
/*
extern BOOLEAN flag_alarm1_sound_on;

void TestMode(void)
{
  BOOLEAN flag_temp = 1;
  INT16U i = KEY_MAX_COUNT+100;

  flag_key1_release = 1;
  flag_key2_release = 1;
    do{
		i--;
		KeyProcess();
		//KeyNumber = GetMyMsg();
		if (KeyNumber == POWER_KEY_L) {
			//Test mode
			sei();
			BuzzOn();
			flag_SDA_sound_on = 1;
			SendDataToVoiceIC(VOLUME_COMMAND,VOLUME_10);
			EraFlash();
			ClearLCD();
			dat[1] = 'V' - 'A' + 10;
			dat[2] = Version[0] - '0';
			dat[3] = 38;
			dat[4] = Version[1] - '0';
			dat[5] = Version[2] - '0';
			DataDisplay();
			//LCDBuffToLCDData();
			McuWriteDataToLcd(0,&SEG1,26);

			while(flag_temp);
       }
	}while(i != 0);
}*/
