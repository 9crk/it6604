///*****************************************
//  Copyright (C) 2009-2014
//  ITE Tech. Inc. All Rights Reserved
//  Proprietary and Confidential
///*****************************************
//   @file   <io.c>
//   @author Jau-Chih.Tseng@ite.com.tw
//   @date   2011/10/26
//   @fileversion: HDMIRX_SAMPLE_2.16
//******************************************/

#include "Mcu.h"
#include "typedef.h"
#ifdef 	_Myson_CS8953_
	#include "CS8953xfr.h"
#endif
#include <intrins.h>
#include <stdio.h>

#include "IO.h"
#include "TimerProcess.h"
#include "hdmirx.h"

BYTE   idata I2CADR; // = RXADR;
BYTE   idata I2CDEV = RXDEV;

#ifdef _Myson_CS8953_

// Header:
// File Name:
// Author:	Liu_CM
// Date:	2009/03/30
// Copyright 2009 Myson Century, Inc.
// http://www.myson.com.tw

// Program Description:
//
// This program demonstrates how to configure the CS8953/66 to transmit and receive by UART interface.
//	The program recive data than transmit it by the UART0 interrupts.
//
// How To Test:
//
// 1) Program example HEX code into MCU.
// 2) Connect serial cable from the transceiver to PC
// 3) On the PC, open Super Terminal (or any other terminal program) and connect
//    to the COM port, the COM port set as 9600bps and 8-N-1
// 4) MCU send ASCII data "CS8966/53" by UART0 after MCU reset.
//		Send data form PC, than PC receive same data.
//
// Target:	CS8953/66
// Hard ware:	eZISP 2.1, PC with COM port.




#define CLEAR_I2CSST	0x0A
#define DEVICE_ID		0x53
#define ENABLE_I2C_ID	(0x80 | DEVICE_ID)

enum
{
	BUSY_FLASH = 0x40,
	FAIL_FLASH = 0x20,
	READ_FLASH = 0x10,
	ERASE_SETOR_FLASH = 0x08,
	WRITE_FLASH = 0x04,
	IFB_READ_FLASH = 0x02,
	IFB_WRITE_FLASH = 0x01
};
#define	ADR_MARCH		(I2CSST1 & 0x40)
#define	ADR_UNMARCH		(!(I2CSST1 & 0x40))
#define	RCBI_OCCUR		(I2CSST1 & 0x04)
#define	RCBI_UNOCCUR	(!(I2CSST1 & 0x04))
#define	TXBI_OCCUR		(I2CSST1 & 0x08)
#define	TXBI_UNOCCUR	(!(I2CSST1 & 0x08))
#define	STOPI_OCCUR		(I2CSST1 & 0x20)
#define	STOPI_UNOCCUR	(!(I2CSST1 & 0x20))
#define RPSTARTI_OCCUR	(I2CSST1 & 0x10)

//------
#define COMMAND_POINT 0x00
#define ADR_MID_POINT 0x01
#define ADR_LOW_POINT 0x02

//------FLASH DEFINE
//#define SUCCESS 0x55
//#define FAIL 0xAA
#define OPEN_TB_REGLOCK() TB = 0xAA ; TB = 0x55
#define REGLOCK TB=0
#define ERASE_SCOPE_MAXPAGE 58
#define mOPEN_FLASHLOCK()	\
		OPEN_TB_REGLOCK();	\
		CNTPCTL1 = 0x00;	\
		CNTPCTH1 = 0x7D

#define mCLOSE_FLASHLOCK	\
		OPEN_TB_REGLOCK();	\
		CNTPCTL1 = 0xFF;	\
		CNTPCTH1 = 0x00
#define BUSYSTAUS	(byFLSHCMD1 & BUSY_FLASH)
#define FAILSTATUS	(byFLSHCMD1 & FAIL_FLASH)

//define for selection XOSC, default is IOSC
#define  measure_VDD2_5    0x0F

// P0~P3 I/O settings
#define InputOnly         0x80//b10000000	//Input Only
#define InputPullUp       0xA0//b10100000	//Input /w Pull Up
#define InputPullDn       0x90//b10010000	//Input /w Pull Down
#define InputBusHolder    0xC0//b11000000	//Input /w Bus Holder
#define OutCMOSPushPull   0x06//b00000110	//Output with COMS Push-Pull
#define OutNMOSOpenDrain  0x02//b00000010	//Output NMOS Open-Drain(sink)
#define OutNMOSWeakPullUp 0x22//b00100010	//Output NMOS Open-Drain(sink) and weak pull up
#define OutPMOSOpenDrain  0x04//b00000100	//Output PMOS Open-Drain(source)
#define OutPMOSWeakPullDn 0x24//b00010100	//Output PMOS Open-Drain(source) and weak pull down
#define IO8051Like        0xE2//b11100010	//8051 Like
#define IOCMOS            0x86//b10000110	//I/O COMS
#define AnalogFunction    0x08//b00001000	//Analog Function
#define OscillatorPin     0x00//b00000000	//Oscillator Pin



//read IFB data
BYTE Read_IFB(BYTE IFB_Address)
{
	BYTE IFB_Data;

	OPEN_TB_REGLOCK();
	FLSHADH1 = 0x00;
	FLSHADL1 = IFB_Address;
	FLSHCMD1 = IFB_READ_FLASH;  //IFB_READ
	TB = 0x00;
	OPEN_TB_REGLOCK();
	IFB_Data = FLSHDAT1;
	TB = 0x00;
	return IFB_Data;
}

//Initial read IFB data
void Initial_SFR(void)
{
	//Port 0 setting

	MFCFGP0_0=0x01;	//PCSCL
	IOCFGP0_0=IO8051Like;

	MFCFGP0_1=0x01;	//PCSDA
	IOCFGP0_1=IO8051Like;

	MFCFGP0_2=0x01;	//DDCSCL
	IOCFGP0_2=IO8051Like;

	MFCFGP0_3=0x01;	//DDCSDA
	IOCFGP0_3=IO8051Like;

	MFCFGP0_4=0x01;
	IOCFGP0_4=IOCMOS;

	MFCFGP0_5=0x01;
	IOCFGP0_5=IOCMOS;

	//MFCFGP0_6=0x02;	//UART TXD
	//IOCFGP0_6=OutCMOSPushPull;
	//MFCFGP0_7=0x02;	//UART RXD
	//IOCFGP0_7=InputPullUp;
	MFCFGP0_6=0x02;	//UART TXD
	IOCFGP0_6=OutCMOSPushPull;
	MFCFGP0_7=0x02;	//UART RXD
	IOCFGP0_7=InputOnly;

	//Port 1 setting
	MFCFGP1_0=0x01;	//DAC_DDCSCL
	IOCFGP1_0=IO8051Like;

	MFCFGP1_1=0x01;	//DAC_DDCSDA
	IOCFGP1_1=IO8051Like;

	MFCFGP1_2=0x02;	//I2C_SDA for IAP
	IOCFGP1_2=IOCMOS;

#if (_DP_6512FN_Myson)
	#pragma message("config IO as 6512FN")
	MFCFGP1_3=0x03;
	IOCFGP1_3=IOCMOS;

	MFCFGP1_4=0x01;
	IOCFGP1_4=IO8051Like;

	MFCFGP1_5=0x01;
	IOCFGP1_5=IO8051Like;

	MFCFGP1_6=0x01;
	IOCFGP1_6=IO8051Like;
#else
	MFCFGP1_3=0x02;	//I2C_SCL for IAP
	IOCFGP1_3=IOCMOS;

	MFCFGP1_4=0x01;
	IOCFGP1_4=IOCMOS;

	MFCFGP1_5=0x01;
	IOCFGP1_5=IOCMOS;

	MFCFGP1_6=0x01;
	IOCFGP1_6=IOCMOS;
#endif
	MFCFGP1_7=0x01;
	IOCFGP1_7=IOCMOS;

	//Port 2 setting
	MFCFGP2_0=0x02;	//XOSC XIN
	IOCFGP2_0=OscillatorPin;
	MFCFGP2_1=0x02;	//XOSC XOUT
	IOCFGP2_1=OscillatorPin;

	MFCFGP3_0=0x01;
	IOCFGP3_0=IOCMOS;

	MFCFGP3_1=0x01;
	IOCFGP3_1=IOCMOS;

	MFCFGP3_2=0x01;
	IOCFGP3_2=IOCMOS;
}

//select XTAL = IOSC as 3.68MHz or XOSC by "#define XOSC"
//setting VDD25=2.5V
void Initial_OSC(void)
{
	BYTE data REGTRM_dat;
	BYTE data IOSCITRM_dat,IOSCVTRM_dat;

	REGTRM_dat = Read_IFB(0x20);
	if(REGTRM_dat == 0xff)
		REGTRM_dat =  measure_VDD2_5;
	OPEN_TB_REGLOCK();
	REGTRM = REGTRM_dat;
	TB = 0x00;

	IOSCITRM_dat = Read_IFB(0x21);
	IOSCVTRM_dat = Read_IFB(0x22);
	if((IOSCITRM_dat > 0x03)||(IOSCITRM_dat == 0xff))
	{
		IOSCITRM_dat = 0x01;
		IOSCVTRM_dat = 0xB0;
	}

	OPEN_TB_REGLOCK();
	IOSCITRM = IOSCITRM_dat;
	IOSCVTRM = IOSCVTRM_dat;
	TB = 0x00;

	#ifdef XOSC_Enable
	IOCFGP2_0 = OscillatorPin;	//set P20 as XOSC
	IOCFGP2_1 = OscillatorPin;	//set P21 as XOSC
	MFCFGP2_0 = 0x02;	//set P20 as XOSC
	MFCFGP2_1 = 0x02;	//set P21 as XOSC
	OPEN_TB_REGLOCK();
	XOSCCFG   = 0x01;	//set XOSC current: 0x00:Power Down; 0x01:12MHz@5V; 0x02:24MHz@5V 0x03:30MHz@5V
	TB = 0x00;
	delay1ms(50);	//necessary for stable crystal.
	//TB = 0xaa;
	//TB = 0x55;
	OPEN_TB_REGLOCK();
	CKSEL = 0x01;		//System Clock Selection Register TB Protected, 0x00:IOSC;	0x01:XOSC;	0x02:RTC;
	TB = 0x00;
	#endif
}


#endif

BYTE i2c_read(BYTE I2CADR, BYTE RegAddr, BYTE ByteNo, BYTE* DataIn)
{
    BYTE p_data;

    i2c_read_byte(I2CADR, RegAddr, ByteNo, &p_data, I2CDEV);

    *DataIn= p_data;

    return p_data;
}



BOOL i2c_write(BYTE I2CADR, BYTE RegAddr, BYTE ByteNo, BYTE DataIn)

{
    BOOL flag;

    flag = i2c_write_byte(I2CADR, RegAddr, ByteNo, &DataIn, I2CDEV);

    return flag;
}

BYTE HDMIRX_ReadI2C_Byte(BYTE RegAddr)
{
    BYTE uc ;
    i2c_read_byte(HDMIRXADR, RegAddr, 1, &uc, RXDEV);
    return uc ;
}

SYS_STATUS HDMIRX_WriteI2C_Byte(BYTE RegAddr,BYTE val)
{
    if( i2c_write_byte(HDMIRXADR, RegAddr, 1, &val, RXDEV) )
    {
        return ER_SUCCESS ;
    }
    return ER_FAIL ;

}


SYS_STATUS HDMIRX_ReadI2C_ByteN(BYTE RegAddr,BYTE *pData,int N)
{
    if( i2c_read_byte(HDMIRXADR, RegAddr,N, pData, RXDEV) )
    {
        return ER_SUCCESS ;
    }
    return ER_FAIL ;
}

SYS_STATUS HDMIRX_WriteI2C_ByteN(BYTE RegAddr,BYTE *pData,int N)
{
    if( i2c_write_byte(HDMIRXADR, RegAddr,N, pData, RXDEV) )
    {
        return ER_SUCCESS ;
    }
    return ER_FAIL ;
}

#ifdef _EDID_Parsing_
BOOL EDID_READ_BYTE( BYTE address, BYTE offset, BYTE byteno, BYTE *p_data, BYTE device)
{
    return i2c_read_byte(address, offset, byteno, p_data, device);

}
BOOL EDID_WRITE_BYTE( BYTE address, BYTE offset, BYTE byteno, BYTE *p_data, BYTE device )
{
    return i2c_write_byte(address, offset, byteno, p_data, device);
}
#endif
///////////////////////////////////////////////////////////////////////////////
// Start: I2C for 8051
///////////////////////////////////////////////////////////////////////////////
void set_8051_scl( BOOL bit_value, BYTE device )
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
    switch( device )
    {
        case RXDEV:
            SCL_PORT    = bit_value;
            break;
#ifdef _EDID_Parsing_
        case ExtEDID:
            VGA_SCL     = bit_value;                // VGA DDC control
            break;
        case IntEDID:
            //printf("bit_SCL=%d\n",bit_value);
            EDID_SCL   = bit_value;
            break;
#endif
        default:
            SCL_PORT    = bit_value;
    }
    //    DelayUS(DELAY_TIME);
}

void set_8051_sda( BOOL bit_value, BYTE device )
{
    switch( device )
    {
        case RXDEV:
            SDA_PORT    = bit_value;
            break;
#ifdef _EDID_Parsing_
        case ExtEDID:
            VGA_SDA     = bit_value;
            break;
        case IntEDID:
            //printf("bit_SDA=%d\n",bit_value);
            EDID_SDA   = bit_value;
            break;
#endif
        default:
            SDA_PORT    = bit_value;
    }
}

BOOL get_8051_sda(BYTE device )
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
    switch( device )
    {
        case RXDEV:
            SDA_PORT    = 1;
            return SDA_PORT;
            break;
#ifdef _EDID_Parsing_
        case ExtEDID:
            VGA_SDA     = 1;
            return VGA_SDA;
            break;
        case IntEDID:
            EDID_SDA   = 1;
            return EDID_SDA;
            break;
#endif
        default:
            SDA_PORT    = 1;
            return SDA_PORT;
    }
}

void i2c_8051_start( BYTE device )
{
    set_8051_sda( HIGH, device );
    set_8051_scl( HIGH, device );
    set_8051_sda( LOW, device );
    set_8051_scl( LOW, device );
}

void i2c_8051_write( BYTE byte_data, BYTE device )
{
    BYTE  bit_cnt, tmp;
    BOOL  bit_value;

    for(bit_cnt=0; bit_cnt<8; bit_cnt++)
    {
        tmp = (byte_data << bit_cnt) & 0x80;
        bit_value = tmp && 0x80;
        set_8051_sda( bit_value, device );
        set_8051_scl( HIGH, device );
        set_8051_scl( LOW, device );
    }
}

BOOL i2c_8051_wait_ack( BYTE device )
{
    BOOL  ack_bit_value;

    set_8051_sda( HIGH, device );
    set_8051_scl( HIGH, device );
    ack_bit_value = get_8051_sda( device );
    set_8051_scl( LOW, device );
    return ack_bit_value;
}

BYTE i2c_8051_read( BYTE device )
{
    BYTE  bit_cnt, byte_data;
    BOOL  bit_value;

    byte_data = 0;
    for(bit_cnt=0; bit_cnt<8; bit_cnt++)
    {
        set_8051_scl( HIGH, device );
        bit_value = get_8051_sda( device );
        byte_data = (byte_data << 1) | bit_value;
        set_8051_scl( LOW, device );
    }

    return byte_data;
}

void i2c_8051_send_ack( BOOL bit_value, BYTE device )
{
     set_8051_sda( bit_value, device );
     set_8051_scl( HIGH, device );
     set_8051_scl( LOW, device );
     set_8051_sda( HIGH, device );
}

void i2c_8051_end( BYTE device )
{
     set_8051_sda( LOW, device );
     set_8051_scl( HIGH, device );
     set_8051_sda( HIGH, device );
}

BOOL i2c_write_byte( BYTE address, BYTE offset, BYTE byteno, BYTE *p_data, BYTE device )
{
    BYTE i;
    i2c_8051_start(device);                // S

    i2c_8051_write(address&0xFE, device);        // slave address (W)
    if( i2c_8051_wait_ack(device)==1 )
    {        // As
        i2c_8051_end(device);
        //printf("w slave address (W)( i2c_8051_wait_ack(device)==1 )\n");
        return 0;
    }

    i2c_8051_write(offset, device);            // offset
    if( i2c_8051_wait_ack(device)==1 )
    {        // As
        i2c_8051_end(device);
        //printf("w offset( i2c_8051_wait_ack(device)==1 )\n");

        return 0;
    }

    for(i=0; i<byteno-1; i++)
    {
        i2c_8051_write(*p_data, device);        // write d
        if( i2c_8051_wait_ack(device)==1 )
        {        // As
            i2c_8051_end(device);

            //printf("w write d( i2c_8051_wait_ack(device)==1 )\n");
            return 0;
        }
        p_data++;
    }

    i2c_8051_write(*p_data, device);            // write last d
    if( i2c_8051_wait_ack(device)==1 )
    {        // As
        i2c_8051_end(device);
        //printf("w  write last d( i2c_8051_wait_ack(device)==1 )\n");

        return 0;
    }
    else
    {
        i2c_8051_end(device);
        return 1;
    }
}


BOOL i2c_read_byte( BYTE address, BYTE offset, BYTE byteno, BYTE *p_data, BYTE device )
{
    BYTE i;

    i2c_8051_start(device);                // S

    i2c_8051_write(address&0xFE, device);        // slave address (W)
    if( i2c_8051_wait_ack(device)==1 )
    {        // As
        i2c_8051_end(device);
        //printf("r slave address (W)( i2c_8051_wait_ack(device)==1 )\n");
        return 0;
    }

    i2c_8051_write(offset, device);            // offset
    if( i2c_8051_wait_ack(device)==1 )
    {        // As
        i2c_8051_end(device);
        //printf("r offset( i2c_8051_wait_ack(device)==1 )\n");

        return 0;
    }

    i2c_8051_start(device);

    i2c_8051_write(address|0x01, device);        // slave address (R)
    if( i2c_8051_wait_ack(device)==1 )
    {        // As
        i2c_8051_end(device);
        //printf("r slave address (R)( i2c_8051_wait_ack(device)==1 )\n");
        return 0;
    }

    for(i=0; i<byteno-1; i++)
    {
        *p_data = i2c_8051_read(device);        // read d
        i2c_8051_send_ack(LOW, device);        // Am

        p_data++;
    }

    *p_data = i2c_8051_read(device);            // read last d
    i2c_8051_send_ack(HIGH, device);            // NAm
    i2c_8051_end(device);

    return 1;
}

///////////////////// Delay Utility ///////////////////////////
void delay1ms(USHORT ms)
{

    while(! IsTimeOut(ms) )
    {
    }
}
#ifndef Debug_message
#endif

void HoldSystem(void)
{
    Hold_Pin=1;
    while(!Hold_Pin)
	{
		printf("Hold\\\r") ;
		printf("Hold-\r") ;
		printf("Hold/\r") ;
		printf("Hold|\r") ;
	}
}

BOOL RXHPD_ENABLE=TRUE ;
USHORT HPDOff_TickCount ;
#define HPDOFF_MIN_PERIOD 2000
void hdmirx_set_hpd()
{
    if( RXHPD_ENABLE == FALSE )
    {
        while(CalTimer(HPDOff_TickCount)<HPDOFF_MIN_PERIOD)
        {
            HDMIRX_DEBUG_PRINTF(("HPDOff_TickCount = %d, ucTickCount = %d\r",HPDOff_TickCount,ucTickCount)) ;
        }
        HDMIRX_DEBUG_PRINTF(("\n")) ;

    	Turn_HDMIRX(ON) ;
        RX_HPD = HIGH ;
        RXHPD_ENABLE = TRUE ;
    }
}

void hdmirx_clear_hpd()
{
    if( RXHPD_ENABLE == TRUE )
    {
        HPDOff_TickCount = ucTickCount ;
    	Turn_HDMIRX(OFF) ;
        RX_HPD = LOW ;
        RXHPD_ENABLE = FALSE ;
    }
}

BOOL DisableVGAChecking()
{
    P1_6 = 1 ;
    if( !P1_6 ) return TRUE ;
    return FALSE ;
}
