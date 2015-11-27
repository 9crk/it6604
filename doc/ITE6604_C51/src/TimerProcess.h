///*****************************************
//  Copyright (C) 2009-2014
//  ITE Tech. Inc. All Rights Reserved
//  Proprietary and Confidential
///*****************************************
//   @file   <timerprocess.h>
//   @author Jau-Chih.Tseng@ite.com.tw
//   @date   2011/10/26
//   @fileversion: HDMIRX_SAMPLE_2.16
//******************************************/


#ifndef _TIMERPROCESS_H
#define _TIMERPROCESS_H
#include "typedef.h"
#include "Mcu.h"
#include "IO.h"
#include "TimerProcess.h"

#ifdef 	_Myson_CS8953_
#include "CS8953sfr.h"
		#define CLOCK           3686400L	 // 10ms => 32ms
        #define MachineCycle    12
#else
    #ifndef CLOCK
    		#define CLOCK           12000000L//11059200L//24000000L////27000000L//12000000L //15000000L
    #else
        #pragma message("CLOCK is predefined.")
    #endif
    #ifndef MachineCycle
        #define MachineCycle    6//6//12
    #else
        #pragma message("MachineCycle is prefdefined.")
    #endif
#endif


#if (CLOCK <= 12000000L)
    #define BAUD_RATE               38400L
    #pragma message("Baud rate are defined as 38400.")
#else
    #define BAUD_RATE               115200L
    #pragma message("Baud rate are defined as 115200.")
#endif

#define BAUD_SETTING            (65536L - ((CLOCK*12/MachineCycle)/(32L * BAUD_RATE)))
//#define BAUD_SETTING            ((256L*16L+8)-((CLOCK*16L)/(192L*BUAD_RATE)))/16L

#define One_Sec                 1000L

extern USHORT idata ucTickCount;

#define MAX_TimerTaskC 1
typedef enum System_TimerTask_Type {
    SysTimerTask_Wait0,
    SysTimerTask_Wait1,
    SysTimerTask_Wait2,
    SysTimerTask_Wait3,
    SysTimerTask_Wait4,
    SysTimerTask_Wait5,
    SysTimerTask_Wait6,
    SysTimerTask_Wait7,
    SysTimerTask_non,
} System_TimerTask_Type;

typedef enum System_TimerTask_Run {
    SysTimerTask_AutoRun,
    SysTimerTask_OnceRun,
    SysTimerTask_NonRun,
} System_TimerTask_Run;


typedef struct TimerTask_Description
{
    unsigned short  TimerTask_TickCount;
    unsigned short  TimerTask_AimCount;
    System_TimerTask_Type  TimerTask_name;
    System_TimerTask_Run    TimerTaskAutoRun;
} TimerTask_Description,*PTimerTask_Description;

void init_timer();
BOOL IsTimeOut(USHORT x);
//volatile TimerTask_Description idata TimerTask[MAX_TimerTaskC];
BYTE TimerTaskCheck();
BYTE MateTimerTask(System_TimerTask_Type cTimerTask);
BYTE NewTimerTaskAlloca();
USHORT CalTimer(ULONG SetupCnt);

//////////////////////////////////////////////////////////////
#endif

