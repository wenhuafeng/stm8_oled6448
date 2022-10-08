

#ifndef _TYPE_DEFINE_H_
#define _TYPE_DEFINE_H_




//********************************************************************************
typedef bool                    BOOLEAN;
typedef unsigned char           INT8U, U8, uint8, UINT8, BYTE;          /* Unsigned  8 bit quantity        */
typedef signed   char           INT8S, S8, int8, INT8;                  /* Signed    8 bit quantity        */
typedef unsigned short int      INT16U, U16, uint16, UINT16, WORD;      /* Unsigned 16 bit quantity        */
typedef signed   short int      INT16S, S16, int16, INT16;              /* Signed   16 bit quantity        */
typedef unsigned int            INT32U, U32, uint32, UINT32, DWORD;     /* Unsigned 32 bit quantity        */
typedef signed   int            INT32S, S32, int32, INT32;              /* Signed   32 bit quantity        */
typedef float                   FP32;                                   /* Single precision floating point */
//********************************************************************************

#define code    const

#ifndef NULL
#define NULL  ((void*)0)
#endif

#define BIG_ENDIAN    1

#if     BIG_ENDIAN
typedef union
  {
    U16 W;
    struct { U8  H; U8  L; } B;
  } WDt;
typedef union
  {
    U32 D;
    struct { U16 H; U16 L; } W;
    struct { U8  M; U8  U; U8  H; U8  L; } B;
  } DWt;
#else
typedef union
  {
    U16 W;
    struct { U8  L; U8  H; } B;
  } WDt;
typedef union
  {
    U32 D;
    struct { U16 L; U16 H; } W;
    struct { U8  L; U8  H; U8  U; U8  M; } B;
  } DWt;
#endif


#define LOWBYTE(X)   ((U8)((X)&0xff))//E!£gII?
#define HIGHBYTE(X)  ((U8)((X)/0x100))//E!¡Ms
//#define HIGHBYTE(X)  ((X)>>8)	//((U8)((X)>>8))//E!¡MsI?
#define BMSK(N)       (1U<<(N))
#define BSET(X,N)     (X)|=BMSK(N)
#define BCLR(X,N)     (X)&=(BMSK(N)^-1)
#define BCPL(X,N)     (X)^=BMSK(N)
#define BTST(X,N)     ((X)&BMSK(N))
#define BSETEX(X,N)   X[(N)>>3]|=((U8)BMSK((N)&7))
#define BCLREX(X,N)   X[(N)>>3]&=(((U8)BMSK((N)&7))^-1)
#define BCPLEX(X,N)   X[(N)>>3]^=((U8)BMSK((N)&7))
#define BTSTEX(X,N)   (X[(N)>>3]&((U8)BMSK((N)&7)))
#define LENOF(ARR)    ((U8)(sizeof(ARR)/sizeof(ARR[0])))
#define ASSIGN(H,L,N) do { H=(U8)((N)/256); L=(U8)((N)%256); } while(0)
#define INCEX(X)     if(++X==0)X--//(X=((X)+1>(X))?(X)+1:(X))
#define DECEX(X)     if(X!=0)X--//(X=((X)-1<(X))?(X)-1:(X))

#endif

