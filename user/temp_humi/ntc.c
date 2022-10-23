#ifndef OS_MASTER_FILE
#define OS_GLOBALS
#include "includes.h"
#endif

#define TMPRREF(x)    ((int16_t)((x) * 10.0))
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define TEMP_MIN      (0)    // 0C
#define TEMP_MAX      (500) // 50C
#define NTC_PULL_UP   (10)   // resistor 10K
#define ADC_BIT_NUM   (4096) // 12bit ADC
#define AD_OF_NTC(r)  ((uint16_t)(r / (r + NTC_PULL_UP) * ADC_BIT_NUM + 0.5))

#if defined(NTC) && (NTC)

static int16_t temperature;

/*
 *  Vj = 3.3 * (Rt / (Rt + Ru))   --- (1)
 *  ADC = (Vj / 3.3) x 4096       --- (2)
 *  ADC = (Rt / (Rt + Ru)) x 4096 --- (3) = (1) + (2)
 *  example:
 *    0 C: (27.78 / (27.78 + 10)) x 4096 + 0.5 = 3011 = BC3
 *    1 C: (26.61 / (26.61 + 10)) x 4096 + 0.5 = 2977 = BA1
 */
static const uint16_t g_ntcTable[] = {
    AD_OF_NTC(324.497),  //  0
    AD_OF_NTC(308.533),  //  1
    AD_OF_NTC(293.440),  //  2
    AD_OF_NTC(279.166),  //  3
    AD_OF_NTC(265.662),  //  4
    AD_OF_NTC(252.884),  //  5
    AD_OF_NTC(240.790),  //  6
    AD_OF_NTC(229.339),  //  7
    AD_OF_NTC(218.495),  //  8
    AD_OF_NTC(208.222),  //  9
    AD_OF_NTC(198.489),  // 10
    AD_OF_NTC(189.263),  // 11
    AD_OF_NTC(180.516),  // 12
    AD_OF_NTC(172.221),  // 13
    AD_OF_NTC(164.352),  // 14
    AD_OF_NTC(156.886),  // 15
    AD_OF_NTC(149.800),  // 16
    AD_OF_NTC(143.072),  // 17
    AD_OF_NTC(136.683),  // 18
    AD_OF_NTC(130.614),  // 19
    AD_OF_NTC(124.847),  // 20
    AD_OF_NTC(119.366),  // 21
    AD_OF_NTC(114.155),  // 22
    AD_OF_NTC(109.199),  // 23
    AD_OF_NTC(104.485),  // 24
    AD_OF_NTC(100.000),  // 25
    AD_OF_NTC(95.7310),  // 26
    AD_OF_NTC(91.6670),  // 27
    AD_OF_NTC(87.7960),  // 28
    AD_OF_NTC(84.1090),  // 29
    AD_OF_NTC(80.5960),  // 30
    AD_OF_NTC(77.2470),  // 31
    AD_OF_NTC(74.0550),  // 32
    AD_OF_NTC(71.0100),  // 33
    AD_OF_NTC(68.1060),  // 34
    AD_OF_NTC(65.3350),  // 35
    AD_OF_NTC(62.6900),  // 36
    AD_OF_NTC(60.1650),  // 37
    AD_OF_NTC(57.7540),  // 38
    AD_OF_NTC(55.4510),  // 39
    AD_OF_NTC(53.2500),  // 40
    AD_OF_NTC(51.1470),  // 41
    AD_OF_NTC(49.1360),  // 42
    AD_OF_NTC(47.2130),  // 43
    AD_OF_NTC(45.3740),  // 44
    AD_OF_NTC(43.6150),  // 45
    AD_OF_NTC(41.9310),  // 46
    AD_OF_NTC(40.3190),  // 47
    AD_OF_NTC(38.7760),  // 48
    AD_OF_NTC(37.2980),  // 49
    AD_OF_NTC(35.8820),  // 50
};

static void SortRoutine(uint16_t *buf, uint8_t num)
{
    uint8_t i, j;
    uint16_t tmp;

    for (i = 0; i < num - 1; i++) {
        for (j = i + 1; j < num; j++) {
            tmp = buf[i];
            if (tmp > buf[j]) {
                buf[i] = buf[j];
                buf[j] = tmp;
            }
        }
    }
}

static uint16_t GetAverageValue(uint16_t *buf, uint8_t num)
{
    uint8_t i;
    uint16_t sum = 0;
    uint16_t average;

    for (i = 1; i < (num - 1); i++) {
        sum += *(buf + i);
    }

    average = sum / (num - 2);
    i       = sum % (num - 2);
    if (i > (num - 2) / 2) {
        average++;
    }

    return average;
}

static uint16_t GetTemperatureAdcValue(void)
{
    uint8_t i;
    uint16_t adBuf[5];
    uint16_t adVal;

    for (i = 0; i < 5; i++) {
        adBuf[i] = ADConversion(ADC_Channel_17);
    }

    SortRoutine(adBuf, 5);
    adVal = GetAverageValue(adBuf, 5);

    return adVal;
}

int16_t NTC_ReadSensor(void)
{
    uint16_t max     = (ARRAY_SIZE(g_ntcTable) - 1);
    uint16_t min     = 0;
    uint16_t average = 0;
    int16_t temp;
    uint16_t value;

    value = GetTemperatureAdcValue();
    if (value >= g_ntcTable[min]) {
        temp = TEMP_MIN;
    } else if (value <= g_ntcTable[max]) {
        temp = TEMP_MAX;
    } else {
        while (1) {
            average = (max - min);
            average = average >> 1;

            if (average == 0) {
                break;
            }

            if (value < g_ntcTable[min + average]) {
                min = average + min;
            } else if (value > g_ntcTable[min + average]) {
                max = average + min;
            } else {
                break;
            }
        }

        temp    = min + average;
        average = TMPRREF(value - g_ntcTable[temp]) / (g_ntcTable[temp + 1] - g_ntcTable[temp]);
        temp    = TMPRREF(temp) + average;
        temp    = (temp + TEMP_MIN);
    }

    temperature = temp;

    return temp;
}

int16_t NTC_GetTemperature(void)
{
    return temperature;
}

#else

int16_t NTC_ReadSensor(void)
{
    return TEMP_MIN;
}

int16_t NTC_GetTemperature(void)
{
    return TEMP_MIN;
}

#endif
