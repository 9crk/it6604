///*****************************************
//  Copyright (C) 2009-2014
//  ITE Tech. Inc. All Rights Reserved
//  Proprietary and Confidential
///*****************************************
//   @file   <mainmcu.c>
//   @author Jau-Chih.Tseng@ite.com.tw
//   @date   2011/10/26
//   @fileversion: HDMIRX_SAMPLE_2.16
//******************************************/


#include "mcu.h"
#include "hdmirx.h"
#include "515XRAM.h"
#include "io.h"
#include "version.h"
#include "edid.h"

#define DUMP_TIME 20

BOOL ReadRXIntPin();

void InitHDMIRX(BOOL bFullInit);
BOOL CheckHDMIRX();
void Initial8051Timer1();
void InitUrt(void);
int dump_vidmode();
int dump_audSts();
void dump_InfoFrame();
/////////////////////////////////////////////////////
// Global Data
/////////////////////////////////////////////////////
int xCntSum, xCntCnt ;

BOOL ReadRXIntPin()
{
	bit i;

	i=P3_2;
	if(i==0)return TRUE;
	else return FALSE;

}

void MCU_init(void)
{
    init_timer();
#ifdef _Myson_CS8953_
    WTST = 0x00;    //set MCU speed for Myson
    Initial_SFR();  //set as GPIO
    Initial_OSC();  //set as External OSC
    P1_4=0;         // No power down
    P1_5=0;
#endif

#ifdef Debug_message
    printf("%s\n",VERSION_STRING);
#endif
}

int main(void)
{
    static BOOL bSignal ;
    BOOL bOldSignal, bChangeMode ;
    int dump_count = 0 ;

    MCU_init() ;
	printf("\n%s\n" , VERSION_STRING);
	HoldSystem();

	hdmirx_clear_hpd();

    EnableHDMIRXVideoOutput(VIDEO_AUTO) ;
    SelectHDMIPort(CAT_HDMI_PORTA);
	InitHDMIRX(TRUE);
	hdmirx_set_hpd();

    xCntCnt = 0 ;
    xCntSum = 0 ;

    while(1){

        HoldSystem();

		if(ReadRXIntPin())
		{
	        Check_HDMInterrupt();
	    }

        #if 0
        // for switching to port B

    	hdmirx_clear_hpd();
        EnableHDMIRXVideoOutput(VIDEO_AUTO) ;
        SelectHDMIPort(CAT_HDMI_PORTB);
    	hdmirx_set_hpd();
        #endif

	    if(IsTimeOut(LOOP_MSEC))
	    {
            dump_count ++ ;

		    bOldSignal = bSignal ;
		    bSignal = CheckHDMIRX();
		    bChangeMode = (bSignal != bOldSignal);


            if(bChangeMode)
            {
                // if Changed Mode ...

    	        if(bSignal)
    	        {
    	            // if signal is TRUE , then ...
                    dump_vidmode();
					if( IsHDMIRXHDMIMode() ) dump_InfoFrame() ;
                    dump_audSts();
    	        }
    	        else
    	        {
    	            // if signal is FALSE , then ...
                    xCntCnt = 0 ;
                    xCntSum = 0 ;

    	        }

    			bChangeMode = FALSE ; // clear bChange Mode action
            }
            else
            {
                // if not change mode, ...
    	        if(bSignal)
    	        {
    	            // if signal is TRUE , then ...
    	            if( (dump_count % 20) == 1 )
    	            {
                        xCntCnt ++ ;
                        xCntSum += getHDMIRXxCnt() ;
                        if( xCntCnt > 40 )
                        {
                            xCntCnt /= 2 ;
                            xCntSum /= 2 ;
                        }

    	            }
    	        }
    	        else
    	        {
    	            // if signal is FALSE , then ...
                    xCntCnt = 0 ;
                    xCntSum = 0 ;
    	        }
            }

            if( dump_count > (DUMP_TIME*1000/20) )
            {
                dump_count = 0 ;
                if( bSignal )
                {
                    dump_vidmode();
                    if( IsHDMIRXHDMIMode() ) dump_InfoFrame() ;
					dump_audSts();

                }
                else
                {
                    printf("There is no signal: Reg10 = %02X Reg12 = %02X Reg64 = %02X Reg65 = %02X\n"
                        ,(int)HDMIRX_ReadI2C_Byte(0x10)
                        ,(int)HDMIRX_ReadI2C_Byte(0x12)
                        ,(int)HDMIRX_ReadI2C_Byte(0x64)
                        ,(int)HDMIRX_ReadI2C_Byte(0x65) ) ;
                }
                printf("\n\n") ;
                DumpHDMIRXReg();
            }
	    }//	if(IsTimeOut(20))

    }
	return 0;
}

int dump_vidmode()
{
    USHORT HActive, VActive ;
    USHORT HTotal, VTotal ;
    ULONG HFreq, VFreq ;
    ULONG PCLK ;

    xCntCnt ++ ;
    xCntSum += getHDMIRXxCnt() ;

    HActive = getHDMIRXHorzActive() ;
    VActive = getHDMIRXVertActive() ;
    HTotal = getHDMIRXHorzTotal() ;
    VTotal = getHDMIRXVertTotal() ;

    PCLK = 27000L * 128;
    PCLK *= (ULONG) xCntCnt ;
    PCLK /= (ULONG) xCntSum ;
    PCLK *= 1000L ; // 100*PCLK ;

    HFreq = PCLK / (ULONG)HTotal ; // HFreq
    VFreq = (HFreq*100) / (ULONG)VTotal ; // VFreq * 100


	printf("\n========================================================================\n") ;
	printf("%s mode\n",IsHDMIRXHDMIMode()?"HDMI":"DVI") ;
    printf("Mode - %dx%d@",HActive,VActive);
    printf("%ld.%02ldHz",VFreq/100,VFreq%100) ;
    switch(getHDMIRXOutputColorDepth())
    {
    case 0x7: printf("@48bits") ; break ;
    case 0x6: printf("@36bits") ; break ;
    case 0x5: printf("@30bits") ; break ;
    case 0x4: printf("@24bits") ; break ;
    default: printf("@No def(24bits)") ; break ;
    }
    printf(", PCLK = %ld.%02ldMHz", PCLK/1000000, (PCLK/10000)%100) ;
    PCLK = xCntSum ;
    PCLK *= 100 ;
    PCLK /= xCntCnt ;
    PCLK -= (ULONG)(xCntSum / xCntCnt)*100 ;
    printf(",xCnt= %d.%02ld\n", xCntSum/xCntCnt,PCLK) ;

    printf("<%4dx%4d>,",HTotal,VTotal);

    printf("H:(%d,%d,%d),"
		,getHDMIRXHorzFrontPorch()
	    ,getHDMIRXHorzSyncWidth()
	    ,getHDMIRXHorzBackPorch());

    printf("V:(%d,%d,%d), "
		,getHDMIRXVertFrontPorch()
	    ,getHDMIRXVertSyncWidth()
	    ,getHDMIRXVertSyncBackPorch());

    printf("VSyncToDE = %d\n",getHDMIRXVertSyncToDE());
	printf("========================================================================\n") ;
    printf("HDCP %s\n",IsHDCPOn()?"ON":"OFF") ;
	printf("========================================================================\n") ;
}

int dump_audSts()
{
    BYTE audio_status ;

	printf("\n========================================================================\n") ;
    audio_status = getHDMIRXAudioStatus() ;
    if( (audio_status & T_AUDIO_MASK)!=T_AUDIO_OFF )
    {
        BYTE ch[5] ;
        if( audio_status == T_AUDIO_HBR )
        {
            printf("Audio input is HBR (High Bit Rate) audio.\n") ;
        }
        else if( audio_status == T_AUDIO_DSD )
        {
            printf("Audio input is DSD (One Bit Audio) audio.\n") ;
        }
        else
        {
            if( audio_status & T_AUDIO_NLPCM )
            {
                printf("Audio input is IEC 61937 compressed audio.\n") ;
            }
            else
            {
                printf("Audio input is IEC 60958 linear PCM audio.\n") ;
            }


            printf("layout %d, ",(audio_status & F_AUDIO_LAYOUT_1)?1:0) ;
            printf("%d source\n", (USHORT)audio_status & 7) ;

            getHDMIRXAudioChannelStatus(ch) ;
            printf("Channel Status: %02X %02X %02X %02X %02X\n",(int)ch[0],(int)ch[1],(int)ch[2],(int)ch[3],(int)ch[4]) ;


        }
    }
    else
    {
        printf("No Audio.\n") ;
    }
	printf("========================================================================\n") ;
}

void
dump_InfoFrame()
{
    xdata BYTE INFOFRAME[31] ;
    int i ;


    if( GetAVIInfoFrame(INFOFRAME) )
    {
        printf("GetAVIInfoFrame():") ;
        for( i = 0 ; i <= (3+(INFOFRAME[2] & 0x1F)) ; i++ )
        {
            printf(" %02X",(int)INFOFRAME[i]) ;
        }
        printf("\n") ;
    }
    else
    {
        printf("Cannot get AVI Infoframe()\n") ;
    }

    if( GetAudioInfoFrame(INFOFRAME) )
    {
        printf("GetAudioInfoFrame():") ;
        for( i = 0 ; i <= (3+(INFOFRAME[2] & 0x1F)) ; i++ )
        {
            printf(" %02X",(int)INFOFRAME[i]) ;
        }
        printf("\n") ;
    }
    else
    {
        printf("Cannot get audio infoframe.\n") ;
    }


    if( GetVENDORSPECInfoFrame(INFOFRAME) )
    {
        printf("GetVENDORSPECInfoFrame():") ;
        for( i = 0 ; i <= (3+(INFOFRAME[2] & 0x1F)) ; i++ )
        {
            printf(" %02X",(int)INFOFRAME[i]) ;
        }
        printf("\n") ;
    }
    else
    {
        printf("Cannot GetVENDORSPECInfoFrame()\n") ;
    }
}
