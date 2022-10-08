#ifndef _KEY_PROCESS_H_
#define _KEY_PROCESS_H_

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
OS_EXT INT8U HoldKeyCtr;

OS_EXT FlagStatus F_Key;
OS_EXT FlagStatus F_PushKey;
OS_EXT FlagStatus F_NewKey;
OS_EXT FlagStatus F_HoldKey;
OS_EXT FlagStatus F_TwoKey;
OS_EXT INT8U Key;
OS_EXT INT8U OldKey;

//---------------------------------------
//timer

//==========================================================================
void ClrIrData(void);
void IRProcess(void);
void ScanKey(void);
FlagStatus HoldKeyCom(void);
void PushKeyFunc(void);
void ReleKeyFunc(void);

#endif
