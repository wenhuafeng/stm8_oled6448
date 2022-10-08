///////////////////////////////////////////////////////////
//                                                       //
//      FileName:   NTC.h                                //
//      time:2018-9-18                                   //
//      Author:���                                      //
///////////////////////////////////////////////////////////

#ifndef _NTC_H_
#define _NTC_H_

typedef struct TEMP_TPR {
    int16_t tempVal;
    uint8_t err;
    uint8_t adCNT;
    uint8_t adERR;
    uint8_t errcnt;

    uint16_t adMIN;
    uint16_t adMAX;
    uint16_t adSUM;
} TEMP_STRUCT;

OS_EXT TEMP_STRUCT tprBoil; //��¯�¶�
//OS_EXT TEMP_STRUCT  tprPTC;            //������PTC�¶�
//OS_EXT TEMP_STRUCT  tprWaterout;        //��ˮ�¶�

//#define AIN_TPR_PTC          1
//#define AIN_TPR_BOIL         9
//#define AIN_TPR_WATEROUT     2

#define TMPRREF(X) ((int16_t)((X)*10.0))

//------------------------------------------------------------------------------
void NTC_Init(void);
void NTC_Check(void);

#endif
