///*****************************************
//  Copyright (C) 2009-2014
//  ITE Tech. Inc. All Rights Reserved
//  Proprietary and Confidential
///*****************************************
//   @file   <debug.h>
//   @author Jau-Chih.Tseng@ite.com.tw
//   @date   2011/01/13
//   @fileversion: HDMIRX_SAMPLE_2.09
//******************************************/

#ifndef _DEBUG_H_
#define _DEBUG_H_

#define Debug_message
#ifndef Debug_message
	#pragma message("not DEFINED DEBUG in debug.h")
	#define HDMITX_DEBUG_PRINTF(x)
	#define HDMITX_DEBUG_PRINTF1(x)
	#define HDMITX_DEBUG_PRINTF2(x)
	#define HDMITX_DEBUG_PRINTF3(x)
	#define HDMIRX_DEBUG_PRINTF(x)
	#define HDMIRX_DEBUG_PRINTF1(x)
	#define HDMIRX_DEBUG_PRINTF2(x)
	#define HDMIRX_DEBUG_PRINTF3(x)
	#define EDID_DEBUG_PRINTF(x)
	#define EDID_DEBUG_PRINTF1(x)
	#define EDID_DEBUG_PRINTF2(x)
	#define EDID_DEBUG_PRINTF3(x)
    #define VGA_DEBUG_PRINTF(x)
#else // DEBUG
#pragma message("DEFINED DEBUG in debug.h")

	#define HDMITX_DEBUG_PRINTF(x) // printf x
	#define HDMIRX_DEBUG_PRINTF(x) printk x
	// #define HDMITX_DEBUG_PRINTF(x)
	// #define HDMIRX_DEBUG_PRINTF(x)

	#define HDMITX_DEBUG_PRINTF1(x) // printf x
	#define HDMITX_DEBUG_PRINTF2(x) // printf x
	#define HDMITX_DEBUG_PRINTF3(x) // printf x
	#define HDMIRX_DEBUG_PRINTF1(x) printk x
	#define HDMIRX_DEBUG_PRINTF2(x) // printf x
	#define HDMIRX_DEBUG_PRINTF3(x) // printf x

	#define EDID_DEBUG_PRINTF(x)  printk x
	#define EDID_DEBUG_PRINTF1(x)  // printf x
	#define EDID_DEBUG_PRINTF2(x)  // printf x
	#define EDID_DEBUG_PRINTF3(x)  // printf x

    #define VGA_DEBUG_PRINTF(x)   // printf x

#endif
#endif // _DEBUG_H_
