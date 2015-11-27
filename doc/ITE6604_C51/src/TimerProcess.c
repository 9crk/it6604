///*****************************************
//  Copyright (C) 2009-2014
//  ITE Tech. Inc. All Rights Reserved
//  Proprietary and Confidential
///*****************************************
//   @file   <timerprocess.c>
//   @author Jau-Chih.Tseng@ite.com.tw
//   @date   2011/10/26
//   @fileversion: HDMIRX_SAMPLE_2.16
//******************************************/

#include "mcu.h"

#include "TimerProcess.h"
#include "IO.h"
volatile USHORT idata ucTickCount;
USHORT prevTickCount = 0 ;
//volatile TimerTask_Description idata TimerTask[MAX_TimerTaskC];
BYTE TimerTaskCheck();
BYTE MateTimerTask(System_TimerTask_Type cTimerTask);
BYTE NewTimerTaskAlloca();
USHORT CalTimer(ULONG SetupCnt);

USHORT CalTimer(ULONG SetupCnt)
{
    if(SetupCnt>ucTickCount)
    {
        return (0xffff-(SetupCnt-ucTickCount));
    }
    else
    {
        return (ucTickCount-SetupCnt);
    }
}

BOOL IsTimeOut(USHORT x)
{
    if(CalTimer(prevTickCount) >= x )
    {
        prevTickCount = ucTickCount ;
        return TRUE ;
    }
    return FALSE ;
}


void init_timer()
{
    TMOD &=0xF0;
    TMOD |=0x01;    // Timer 0,Mode 0,16 bit
    TH0=(65536L-(CLOCK/(1000L*MachineCycle))) >> 8;
    TL0=(65536L-(CLOCK/(1000L*MachineCycle)));
    ET0=TRUE;
    TR0=TRUE;
////////////////////////////////////////////////////////////////
#ifdef Debug_message
#if 0
    SCON = 0x50;        /* Setup serial port control register */
                        /* Mode 1: 8-bit uart var. baud rate */
                        /* REN: enable receiver */
    PCON &= 0x7F;       /* Clear SMOD bit in power ctrl reg */
    PCON |= 0x80;       /* This bit doubles the baud rate */
    TMOD &= 0xCF;       /* Setup timer/counter mode register */
                        /* Clear M1 and M0 for timer 1 */
    TMOD |= 0x20;       /* Set M1 for 8-bit autoreload timer */
    TH1 = BAUD_SETTING;
    TR1 = 1;            /* Start timer 1 */
    TI = 1;             /* Set TI to indicate ready to xmit */
#endif
#ifndef _DP_6512_V40_STC
#define _DP_6512_V40_STC  0
#endif

#if (_DP_6512_V40_STC)
    TMOD &=0x0F;
    TMOD |=0x20;    // Timer 1,Mode 2,8 bit
    TH1 = 256-(CLOCK/(BAUD_RATE*384));//242;//256-(28800/9600);//BAUD_SETTING >> 8;
    SCON = 0x52;   //  For stdio.h (printf),  TI(SCON[1]) must set to "1"
    TR1=FALSE;
    TR1=TRUE;
#else
    TL2 = BAUD_SETTING;
    TH2 = BAUD_SETTING >> 8;
    RCAP2L = BAUD_SETTING;
    RCAP2H = BAUD_SETTING >> 8;

    SCON = 0x52;   //  For stdio.h (printf),  TI(SCON[1]) must set to "1"
    T2CON = 0x34;
    TR2 = FALSE;
    TR2 = TRUE;
#endif
#endif
////////////////////////////////////////////////////////////////
    EA=TRUE;
}

///////////////////////////////////////////////////////////////////////
void int_t0() interrupt 1// using 2
{
//             1000                                  CLOCK
//1ms=------------------------------------=---------------------
//        1000000(u sec)                         1000*MachineCycle
//      ---------------- * MachineCycle
//           CLOCK
    TH0=(65536L-(CLOCK/(1000L*MachineCycle))) >> 8;
    TL0=(65536L-(CLOCK/(1000L*MachineCycle)));
    ucTickCount++;

}

