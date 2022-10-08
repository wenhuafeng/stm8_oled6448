///////////////////////////////////////////////////////////
//                                                       //
//      FileName:   NTC.h                                //
//      time:2018-9-18                                   //
//      Author:振邦                                      //
///////////////////////////////////////////////////////////

#ifndef _NTC_H_
#define _NTC_H_

typedef struct TEMP_TPR {
    s16 tempVal;
    U8 err;
    U8 adCNT;
    U8 adERR;
    u8 errcnt;

    U16 adMIN;
    U16 adMAX;
    U16 adSUM;
} TEMP_STRUCT;

OS_EXT TEMP_STRUCT tprBoil; //锅炉温度
//OS_EXT TEMP_STRUCT  tprPTC;            //保温盘PTC温度
//OS_EXT TEMP_STRUCT  tprWaterout;        //出水温度

//#define AIN_TPR_PTC          1
//#define AIN_TPR_BOIL         9
//#define AIN_TPR_WATEROUT     2

#define TMPRREF(X) ((S16)((X)*10.0))

//------------------------------------------------------------------------------
void NTC_Init(void);
void NTC_Check(void);

#endif
