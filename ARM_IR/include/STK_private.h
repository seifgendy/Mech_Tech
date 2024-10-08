#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

 /** STK Registers Definations **/
typedef struct
{
  volatile u32 CTRL;
  volatile u32 LOAD;
  volatile u32 VAL;
  volatile u32 CALIB;
}STK_t;

// Struct Pointer Defination
#define  STK  ((volatile STK_t *) 0xE000E010)

 /*** Bits Definations ***/
#define   STK_BIT_0   0
#define   STK_BIT_1   1
#define   STK_BIT_2   2
#define   STK_BIT_3   3
#define   STK_BIT_4   4
#define   STK_BIT_5   5
#define   STK_BIT_6   6
#define   STK_BIT_7   7
#define   STK_BIT_8   8
#define   STK_BIT_9   9
#define   STK_BIT_10  10
#define   STK_BIT_11  11
#define   STK_BIT_12  12
#define   STK_BIT_13  13
#define   STK_BIT_14  14
#define   STK_BIT_15  15
#define   STK_BIT_16  16
#define   STK_BIT_17  17
#define   STK_BIT_18  18
#define   STK_BIT_19  19
#define   STK_BIT_20  20
#define   STK_BIT_21  21
#define   STK_BIT_22  22
#define   STK_BIT_23  23
#define   STK_BIT_24  24
#define   STK_BIT_25  25
#define   STK_BIT_26  26
#define   STK_BIT_27  27
#define   STK_BIT_28  28
#define   STK_BIT_29  29
#define   STK_BIT_30  30
#define   STK_BIT_31  31

 /** STK AHB Division Factor Definations **/
#define     STK_AHB_DIV_1   0
#define     STK_AHB_DIV_8   1

 /** STK Enable/Disable Definations **/
#define     STK_DISABLE     0
#define     STK_ENABLE      1

// Number Defination
#ifndef  ZERO
#define  ZERO  0
#endif

#define     SINGLE_INTERVAL     0
#define     PERIODIC_INTERVAL   1

#endif
