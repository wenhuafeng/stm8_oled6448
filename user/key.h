#ifndef __KEY_H__
#define __KEY_H__

#define _KEY_MAX_COUNT_       2000
#define _KEY_LONG_PRESS_TIME_ 12 //(120/10)

extern BOOLEAN LongOnce;
extern INT8U KeyNumber;
extern INT8U Time10Ms_keyLongPress;
extern BOOLEAN LongPress;

#define K1  1
#define K2  2
#define K3  3
#define K4  4
#define K5  5
#define K6  6
#define K7  7
#define K8  8
#define K9  9
#define K10 10
#define K11 11
#define K12 12
#define K13 13
#define K14 14
#define K15 15
#define K16 16

//最高两位标记按键状态
#define KEY_DOWN      0x00 /*按下时触发*/
#define KEY_TIME_LONG 0x40 /*长按开始一次*/
#define KEY_SWITCH    0x80 /*Keys function transformation*/

//key1
#define LAMP_KEY    (K6)
#define LAMP_UP_KEY (K5)
#define DOWN_KEY    (K4)
#define UP_KEY      (K3)
#define VOLUP_KEY   (K2)
#define VOLDOWN_KEY (K1)
//key2
#define LAMP_DOWN_KEY (K14)
#define POWER_KEY     (K13)
#define AMS_KEY       (K12)
#define PRESET_KEY    (K11)
#define MODE_KEY      (K10)
#define SNOOZE_KEY    (K9)

//key1
#define LAMP_KEY_L    (LAMP_KEY | KEY_TIME_LONG)
#define LAMP_UP_KEY_L (LAMP_UP_KEY | KEY_TIME_LONG)
#define UP_KEY_L      (UP_KEY | KEY_TIME_LONG)
#define DOWN_KEY_L    (DOWN_KEY | KEY_TIME_LONG)
#define VOLUP_KEY_L   (VOLUP_KEY | KEY_TIME_LONG)
#define VOLDOWN_KEY_L (VOLDOWN_KEY | KEY_TIME_LONG)
//key2
#define LAMP_DOWN_KEY_L (LAMP_DOWN_KEY | KEY_TIME_LONG)
#define POWER_KEY_L     (POWER_KEY | KEY_TIME_LONG)
#define AMS_KEY_L       (AMS_KEY | KEY_TIME_LONG)
#define PRESET_KEY_L    (PRESET_KEY | KEY_TIME_LONG)
#define MODE_KEY_L      (MODE_KEY | KEY_TIME_LONG)
#define SNOOZE_KEY_L    (SNOOZE_KEY | KEY_TIME_LONG)

//=====================================================================================
//共用键定义

#define AL1_KEY   VOLDOWN_KEY
#define AL1_KEY_L VOLDOWN_KEY_L

#define AL2_KEY   VOLUP_KEY
#define AL2_KEY_L VOLUP_KEY_L

#define SET_KEY   MODE_KEY
#define SET_KEY_L MODE_KEY_L

#define SLEEP_KEY   (POWER_KEY | KEY_SWITCH)
#define SLEEP_KEY_L (POWER_KEY_L) //   | KEY_SWITCH)

#define NAP_KEY   (SNOOZE_KEY | KEY_SWITCH)
#define NAP_KEY_L (SNOOZE_KEY_L) //  | KEY_SWITCH)

#define MEM_KEY   AMS_KEY
#define MEM_KEY_L AMS_KEY_L

#define PLAYST_KEY   PRESET_KEY
#define PLAYST_KEY_L PRESET_KEY_L

#define PRESETUP_KEY   (UP_KEY | KEY_SWITCH)
#define PRESETDOWN_KEY (DOWN_KEY | KEY_SWITCH)

//=======================================================================================
void InitADC(void);
INT8U GetKey(INT8U ch, INT8U ad_value);
INT8U ADCChannelGet(INT8U ch);
void TestMode(void);
void VersionView();

void KeyADC_Init(void);
void KeyProcess(void);

#endif
