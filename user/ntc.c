
///////////////////////////////////////////////////////////
//                                                       //
//          FileName:   NTC.c                            //
//          time:2018-9-18                               //
//          Author:振邦                                  //
///////////////////////////////////////////////////////////

#ifndef  OS_MASTER_FILE
#define  OS_GLOBALS
#include "common.h"
#endif

#if (_NTC_)

//#define _NTC_SRC_
#define AD_OF_NTC(R)    ((U16)(2/(2+(R))*1024+0.5))

CONST U16 adNTC_3950_100K[ ] =
{
    AD_OF_NTC( 324.497 ), //  0
    AD_OF_NTC( 308.533 ), //  1
    AD_OF_NTC( 293.440 ), //  2
    AD_OF_NTC( 279.166 ), //  3
    AD_OF_NTC( 265.662 ), //  4
    AD_OF_NTC( 252.884 ), //  5
    AD_OF_NTC( 240.790 ), //  6
    AD_OF_NTC( 229.339 ), //  7
    AD_OF_NTC( 218.495 ), //  8
    AD_OF_NTC( 208.222 ), //  9

    AD_OF_NTC( 198.489 ), // 10
    AD_OF_NTC( 189.263 ), // 11
    AD_OF_NTC( 180.516 ), // 12
    AD_OF_NTC( 172.221 ), // 13
    AD_OF_NTC( 164.352 ), // 14
    AD_OF_NTC( 156.886 ), // 15
    AD_OF_NTC( 149.800 ), // 16
    AD_OF_NTC( 143.072 ), // 17
    AD_OF_NTC( 136.683 ), // 18
    AD_OF_NTC( 130.614 ), // 19

    AD_OF_NTC( 124.847 ), // 20
    AD_OF_NTC( 119.366 ), // 21
    AD_OF_NTC( 114.155 ), // 22
    AD_OF_NTC( 109.199 ), // 23
    AD_OF_NTC( 104.485 ), // 24
    AD_OF_NTC( 100.000 ), // 25
    AD_OF_NTC( 95.731 ),  // 26
    AD_OF_NTC( 91.667 ),  // 27
    AD_OF_NTC( 87.796 ),  // 28
    AD_OF_NTC( 84.109 ),  // 29

    AD_OF_NTC( 80.596 ),  // 30
    AD_OF_NTC( 77.247 ),  // 31
    AD_OF_NTC( 74.055 ),  // 32
    AD_OF_NTC( 71.010 ),  // 33
    AD_OF_NTC( 68.106 ),  // 34
    AD_OF_NTC( 65.335 ),  // 35
    AD_OF_NTC( 62.690 ),  // 36
    AD_OF_NTC( 60.165 ),  // 37
    AD_OF_NTC( 57.754 ),  // 38
    AD_OF_NTC( 55.451 ),  // 39

    AD_OF_NTC( 53.25 ),   // 40
    AD_OF_NTC( 51.147 ),  // 41
    AD_OF_NTC( 49.136 ),  // 42
    AD_OF_NTC( 47.213 ),  // 43
    AD_OF_NTC( 45.374 ),  // 44
    AD_OF_NTC( 43.615 ),  // 45
    AD_OF_NTC( 41.931 ),  // 46
    AD_OF_NTC( 40.319 ),  // 47
    AD_OF_NTC( 38.776 ),  // 48
    AD_OF_NTC( 37.298 ),  // 49
    AD_OF_NTC( 35.882 ),  // 50
    AD_OF_NTC( 34.531 ),  // 51
    AD_OF_NTC( 33.239 ),  // 52
    AD_OF_NTC( 32.00  ),  // 53
    AD_OF_NTC( 30.815 ),  // 54
    AD_OF_NTC( 29.679 ),  // 55
    AD_OF_NTC( 28.59  ),  // 56
    AD_OF_NTC( 27.547 ),  // 57
    AD_OF_NTC( 26.547 ),  // 58
    AD_OF_NTC( 25.588 ),  // 59
    AD_OF_NTC( 24.669 ),  // 60
    AD_OF_NTC( 23.788 ),  // 61
    AD_OF_NTC( 22.942 ),  // 62
    AD_OF_NTC( 22.130 ),  // 63
    AD_OF_NTC( 21.352 ),  // 64
    AD_OF_NTC( 20.604 ),  // 65
    AD_OF_NTC( 19.887 ),  // 66
    AD_OF_NTC( 19.198 ),  // 67
    AD_OF_NTC( 18.536 ),  // 68
    AD_OF_NTC( 17.901 ),  // 69
    AD_OF_NTC( 17.290 ),  // 70
    AD_OF_NTC( 16.703 ),  // 71
    AD_OF_NTC( 16.139 ),  // 72
    AD_OF_NTC( 15.597 ),  // 73
    AD_OF_NTC( 15.076 ),  // 74
    AD_OF_NTC( 14.575 ),  // 75
    AD_OF_NTC( 14.093 ),  // 76
    AD_OF_NTC( 13.629 ),  // 77
    AD_OF_NTC( 13.183 ),  // 78
    AD_OF_NTC( 12.753 ),  // 79
    AD_OF_NTC( 12.340 ),  // 80
    AD_OF_NTC( 11.942 ),  // 81
    AD_OF_NTC( 11.559 ),  // 82
    AD_OF_NTC( 11.190 ),  // 83
    AD_OF_NTC( 10.834 ),  // 84
    AD_OF_NTC( 10.492 ),  // 85
    AD_OF_NTC( 10.162 ),  // 86
    AD_OF_NTC( 9.844 ),   // 87
    AD_OF_NTC( 9.537 ),   // 88
    AD_OF_NTC( 9.242 ),   // 89
    AD_OF_NTC( 8.957 ),   // 90
    AD_OF_NTC( 8.682 ),   // 91
    AD_OF_NTC( 8.417 ),   // 92
    AD_OF_NTC( 8.161 ),   // 93
    AD_OF_NTC( 7.914 ),   // 94
    AD_OF_NTC( 7.676 ),   // 95
    AD_OF_NTC( 7.446 ),   // 96
    AD_OF_NTC( 7.224 ),   // 97
    AD_OF_NTC( 7.010 ),   // 98
    AD_OF_NTC( 6.803 ),   // 99
    AD_OF_NTC( 6.603 ),   // 100
    AD_OF_NTC( 6.410 ),   // 101
    AD_OF_NTC( 6.223 ),   // 102
    AD_OF_NTC( 6.043 ),   // 103
    AD_OF_NTC( 5.868 ),   // 104
    AD_OF_NTC( 5.70 ),    // 105
    AD_OF_NTC( 5.537 ),   // 106
    AD_OF_NTC( 5.38 ),    // 107
    AD_OF_NTC( 5.227 ),   // 108
    AD_OF_NTC( 5.080 ),   // 109
    AD_OF_NTC( 4.937 ),   // 110
    AD_OF_NTC( 4.799 ),   // 111
    AD_OF_NTC( 4.666 ),   // 112
    AD_OF_NTC( 4.537 ),   // 113
    AD_OF_NTC( 4.412 ),   // 114
    AD_OF_NTC( 4.291 ),   // 115
    AD_OF_NTC( 4.174 ),   // 116
    AD_OF_NTC( 4.060 ),   // 117
    AD_OF_NTC( 3.951 ),   // 118
    AD_OF_NTC( 3.844 ),   // 119
    AD_OF_NTC( 3.740 ),   // 120
    AD_OF_NTC( 3.641 ),   // 121
    AD_OF_NTC( 3.544 ),   // 122
    AD_OF_NTC( 3.450 ),   // 123
    AD_OF_NTC( 3.359 ),   // 124
    AD_OF_NTC( 3.270 ),   // 125
    AD_OF_NTC( 3.185 ),   // 126
    AD_OF_NTC( 3.102 ),   // 127
    AD_OF_NTC( 3.021 ),   // 128
    AD_OF_NTC( 2.947 ),   // 129
    AD_OF_NTC( 2.868 ),   // 130
    AD_OF_NTC( 2.794 ),   // 131
    AD_OF_NTC( 2.723 ),   // 132
    AD_OF_NTC( 2.654 ),   // 133
    AD_OF_NTC( 2.586 ),   // 134
    AD_OF_NTC( 2.521 ),   // 135
    AD_OF_NTC( 2.458 ),   // 136
    AD_OF_NTC( 2.396 ),   // 137
    AD_OF_NTC( 2.337 ),   // 138
    AD_OF_NTC( 2.279 ),   // 139
    AD_OF_NTC( 2.222 ),   // 140

    AD_OF_NTC( 2.168 ),    // 141
    AD_OF_NTC( 2.114 ),   // 142
    AD_OF_NTC( 2.063 ),   // 143
    AD_OF_NTC( 2.013 ),   // 144
    AD_OF_NTC( 1.964 ),   // 145
    AD_OF_NTC( 1.916 ),   // 146
    AD_OF_NTC( 1.870 ),   // 147
    AD_OF_NTC( 1.825 ),   // 148
    AD_OF_NTC( 1.782 ),   // 149
    AD_OF_NTC( 1.739 ),   // 150
    AD_OF_NTC( 1.699 ),    // 151

    AD_OF_NTC( 1.659 ),    // 152
    AD_OF_NTC( 1.620 ),   // 153
    AD_OF_NTC( 1.583 ),   // 154
    AD_OF_NTC( 1.546 ),   // 155
    AD_OF_NTC( 1.511 ),   // 156
    AD_OF_NTC( 1.476 ),   // 157
    AD_OF_NTC( 1.442 ),   // 158
    AD_OF_NTC( 1.410 ),   // 159
    AD_OF_NTC( 1.378 ),   // 160
    AD_OF_NTC( 1.347 ),   // 161
    AD_OF_NTC( 1.317 ),    // 162
    AD_OF_NTC( 1.287 ),    // 163
    AD_OF_NTC( 1.259 ),   // 164
    AD_OF_NTC( 1.231 ),   // 165
    AD_OF_NTC( 1.204 ),   // 166
    AD_OF_NTC( 1.178 ),   // 167
    AD_OF_NTC( 1.152 ),   // 168
    AD_OF_NTC( 1.127 ),   // 169
    AD_OF_NTC( 1.102 ),   // 170
    AD_OF_NTC( 1.079 ),   // 171
    AD_OF_NTC( 1.056 ),   // 172
    AD_OF_NTC( 1.033 ),    // 173
};

/*-------------------------------------------------------
FunctionName  : TempInitFun
Description   : 温度检测初始化函数
Input         : 无
OutPut        : 无
Author        : 振邦
Date          : 2018.9.17
Other         : 注意事项、修改记录、函数版本等
--------------------------------------------------------*/
void NTC_Init(void)
{
  u16 temp;

  temp = adNTC_3950_100K[0];
  tprBoil.tempVal     = temp;

//    memset(&tprBoil,    0, sizeof(tprBoil));
//    memset(&tprPTC,     0, sizeof(tprPTC));
//    memset(&tprWaterout,0, sizeof(tprWaterout));
    //tprBoil.tempVal     = TMPRREF(25);
    //tprPTC.tempVal      = TMPRREF(25);
    //tprWaterout.tempVal = TMPRREF(25);
}

/*-------------------------------------------------------
FunctionName  : CalTempFun
Description   : 温度计算函数
Input         : ad值  ad表
OutPut        : TMPRREF(x)温度值
Author        : 振邦
Date          : 2018.9.17
Other         : 注意事项、修改记录、函数版本等
--------------------------------------------------------*/
static  S16 CalTempFun(u16 val,U16 CONST * tab,u8 lenth)
{
    u16 lop_max, lop_min;
    u16 avarg;
    s16  ret;
    lop_min = 0;
    lop_max = lenth - 1;
    avarg = 0;

    if(val <= tab[lop_min])
    {

        ret = TMPRREF(lop_min);
    }
    else if(val >= tab[lop_max])
    {

        ret = TMPRREF(lop_max);
    }
    else
    {
        while(1)
        {
            avarg = (lop_max - lop_min);
            avarg = avarg >> 1;

            if(avarg == 0)break;

            if(val > tab[lop_min + avarg])lop_min = avarg + lop_min;
            else if(val < tab[lop_min + avarg])lop_max = avarg + lop_min;
            else break;
        }

        ret = lop_min + avarg;
        avarg = TMPRREF(val - tab[ret])  / (tab[ret + 1] - tab[ret]);
        ret = TMPRREF(ret)  + avarg;
    }

    return  ret;
}

/*-------------------------------------------------------
FunctionName  : ADC_Collect
Description   : ad滤波采样函数
Input         : ad通道channel   数据接收结构体 str
OutPut        : no:0         complete：1
Author        : 振邦
Date          : 2018.9.17
Other         : 注意事项、修改记录、函数版本等
--------------------------------------------------------*/
u8 ADC_Collect(ADC_Channel_TypeDef channel, TEMP_STRUCT *str)
{
    u16 tmp;
    u8 ret = 0;

    if (str != NULL) {
        tmp = ADConversion(channel);
        tmp = (tmp >> 0x02);
        if (tmp > 1010) {
            INCEX(str->errcnt);
            str->adERR = 2;
        }
        else if(tmp < 6) {
            INCEX(str->errcnt);
            str->adERR = 1;
        }
        else {
            str->adERR = 0;
            str->errcnt = 0;

            if (tmp > str->adMAX) str->adMAX = tmp;
            if (tmp < str->adMIN) str->adMIN = tmp;

            str->adSUM += tmp;
            str->adCNT++;

            if (str->adCNT >= 6) {
                str->adCNT = 0;
                str->adSUM = str->adSUM - str->adMAX - str->adMIN;
                str->adSUM = str->adSUM >> 2;
                str->adMAX = 0;
                str->adMIN = 0xffff;
                ret = 1;
            }
        }
        if (str->errcnt > 30) str->err = str->adERR;
        else str->err = 0;
    }

    return ret;
}

/*-------------------------------------------------------
FunctionName  : NtcCheckFun
Description   : 温度检测处理函数
Input         : 无
OutPut        : tprBoil  tprPTC  tprWaterout
Author        : 振邦
Date          : 2018.9.17
Other         : 注意事项、修改记录、函数版本等
--------------------------------------------------------*/
void NTC_Check(void)
{
    static U8 step = 0;
    switch(step)
    {
        default:
        case 0:
          if(ADC_Collect(ADC_Channel_17, &tprBoil))
          {
              tprBoil.tempVal=CalTempFun(tprBoil.adSUM, adNTC_3950_100K,LENOF(adNTC_3950_100K));
              tprBoil.adSUM=0;
          }
          step=1;
          break;
    }
}

#endif

