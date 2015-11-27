///*****************************************
//  Copyright (C) 2009-2014
//  ITE Tech. Inc. All Rights Reserved
//  Proprietary and Confidential
///*****************************************
//   @file   <mcu.h>
//   @author Jau-Chih.Tseng@ite.com.tw
//   @date   2011/01/13
//   @fileversion: HDMIRX_SAMPLE_2.09
//******************************************/

///////////////////////////////////////////////////////////////////////////////
// Include file
///////////////////////////////////////////////////////////////////////////////
#ifndef _MCU_H_
#define _MCU_H_

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/delay.h>

#include "config.h"

///////////////////////////////////////////////////////////////////////////////
// Global Definition
///////////////////////////////////////////////////////////////////////////////
//#define DIVA
///////////////////////////////////////////////////////////////////////////////
// Type Definition
///////////////////////////////////////////////////////////////////////////////
#include "typedef.h"
#include "debug.h"
#include "io.h"
//#include "TimerProcess.h"
///////////////////////////////////////////////////////////////////////////////
// Constant Definition
///////////////////////////////////////////////////////////////////////////////
#define HDMIRXADR       0x90
#define RXDEV           0
#define ExtEDID         1
#define IntEDID         2


#define RXADR           0xB0

#define DELAY_TIME      1           // unit = 1 us;
#define IDLE_TIME       100         // unit = 1 ms;

#define HIGH            1
#define LOW             0

#define ACTIVE          1
#define DISABLE         0

#define DevNum          1
#define LOOPMS          20          // 20-> 5 ,  030408, Clive
///////////////////////////////////////////////////////////////////////////////
// 8051 Definition
///////////////////////////////////////////////////////////////////////////////
    #define _DP_6504_6902_Dongle_MegaWin    DISABLE//1
    #define _DP_6504_6902_Dongle_Myson      ACTIVE//2
    #define _DP_6506_Demo_V10_MegaWin       DISABLE//3
    #define _DP_6506_Demo_V12_MegaWin       DISABLE//4
    #define _DP_6512_V10_V20_MegaWin        DISABLE//5
    #define _DP_6512_V30_Myson              DISABLE//6
    #define _DP_6512_V40_STC                DISABLE//7
    #define _DP_6512FN_Myson                DISABLE//8

    #ifndef DISABLE_EDID_PARSING
    #define _EDID_Parsing_
    #endif


#define delay1ms(ms) mdelay(ms)

#endif      // _MCU_H_
