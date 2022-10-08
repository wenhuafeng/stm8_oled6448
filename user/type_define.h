#ifndef TYPE_DEFINE_H
#define TYPE_DEFINE_H

//typedef bool BOOLEAN;
//typedef unsigned char uint8_t;       /* Unsigned  8 bit quantity        */
//typedef signed char int8_t;          /* Signed    8 bit quantity        */
//typedef unsigned short int uint16_t; /* Unsigned 16 bit quantity        */
//typedef signed short int int16_t;    /* Signed   16 bit quantity        */
//typedef unsigned int uint32_t;       /* Unsigned 32 bit quantity        */
//typedef signed int int32_t;          /* Signed   32 bit quantity        */
typedef float FP32;                  /* Single precision floating point */

#define code const

#ifndef NULL
#define NULL ((void *)0)
#endif

#define BIG_ENDIAN 1

#if BIG_ENDIAN
typedef union {
    uint16_t W;
    struct {
        uint8_t H;
        uint8_t L;
    } B;
} WDt;
typedef union {
    uint32_t D;
    struct {
        uint16_t H;
        uint16_t L;
    } W;
    struct {
        uint8_t M;
        uint8_t U;
        uint8_t H;
        uint8_t L;
    } B;
} DWt;
#else
typedef union {
    uint16_t W;
    struct {
        uint8_t L;
        uint8_t H;
    } B;
} WDt;
typedef union {
    uint32_t D;
    struct {
        uint16_t L;
        uint16_t H;
    } W;
    struct {
        uint8_t L;
        uint8_t H;
        uint8_t U;
        uint8_t M;
    } B;
} DWt;
#endif

#define LOWBYTE(X)  ((uint8_t)((X)&0xff))    //E!�gII?
#define HIGHBYTE(X) ((uint8_t)((X) / 0x100)) //E!�Ms
//#define HIGHBYTE(X)  ((X)>>8)	//((uint8_t)((X)>>8))//E!�MsI?
#define BMSK(N)      (1U << (N))
#define BSET(X, N)   (X) |= BMSK(N)
#define BCLR(X, N)   (X) &= (BMSK(N) ^ -1)
#define BCPL(X, N)   (X) ^= BMSK(N)
#define BTST(X, N)   ((X)&BMSK(N))
#define BSETEX(X, N) X[(N) >> 3] |= ((uint8_t)BMSK((N)&7))
#define BCLREX(X, N) X[(N) >> 3] &= (((uint8_t)BMSK((N)&7)) ^ -1)
#define BCPLEX(X, N) X[(N) >> 3] ^= ((uint8_t)BMSK((N)&7))
#define BTSTEX(X, N) (X[(N) >> 3] & ((uint8_t)BMSK((N)&7)))
#define LENOF(ARR)   ((uint8_t)(sizeof(ARR) / sizeof(ARR[0])))
#define ASSIGN(H, L, N)           \
    do {                          \
        H = (uint8_t)((N) / 256); \
        L = (uint8_t)((N) % 256); \
    } while (0)
#define INCEX(X)  \
    if (++X == 0) \
    X-- //(X=((X)+1>(X))?(X)+1:(X))
#define DECEX(X) \
    if (X != 0)  \
    X-- //(X=((X)-1<(X))?(X)-1:(X))

#endif
