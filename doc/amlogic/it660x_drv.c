/*
 * Amlogic M6 
 * frame buffer driver-----------HDMI_RX
 * Copyright (C) 2010 Amlogic, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the named License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */
#define HDMI_DEBUG()  printk("HDMI DEBUG: %s [%d]", __FUNCTION__, __LINE__)

#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <linux/major.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h> 
#include <asm/uaccess.h>
#include <mach/am_regs.h>
#include <linux/tvin/tvin_v4l2.h>

//#include "mcu.h"
#include "hdmirx.h"
#include "version.h"
#include "edid.h"
#include "dvin.h"

//#define DEBUG_DVIN

#define DEVICE_NAME "it660x"
#define HDMI_RX_COUNT 4

#define pr_dbg(fmt, args...) printk(KERN_DEBUG "it660x_hdmirx: " fmt, ## args)
#define pr_error(fmt, args...) printk(KERN_ERR "it660x_hdmirx: " fmt, ## args)

//GPIOD_4
#define ENABLE_HPD_MUX   WRITE_MPEG_REG_BITS(PREG_PAD_GPIO2_EN_N, 0, 20, 1)
#define SET_HPD          WRITE_MPEG_REG_BITS(PREG_PAD_GPIO2_O, 1, 20, 1)
#define CLEAR_HPD          WRITE_MPEG_REG_BITS(PREG_PAD_GPIO2_O, 0, 20, 1)
//GPIOD_6
#define ENABLE_SYSRSTN_MUX   WRITE_MPEG_REG_BITS(PREG_PAD_GPIO2_EN_N, 0, 22, 1)
#define RESET_SYSRSTN        WRITE_MPEG_REG_BITS(PREG_PAD_GPIO2_O, 1, 22, 1)
#define RELEASE_SYSRSTN      WRITE_MPEG_REG_BITS(PREG_PAD_GPIO2_O, 0, 22, 1)

#ifdef CONFIG_AML_AUDIO_DSP
#define M2B_IRQ0_DSP_AUDIO_EFFECT (7)
#define DSP_CMD_SET_HDMI_SR   (6)
extern int  mailbox_send_audiodsp(int overwrite,int num,int cmd,const char *data,int len);
#endif

static dev_t hdmirx_id;
static struct class *hdmirx_class;
static struct device *hdmirx_dev;

int it660x_debug_flag = 0;
static int stable_threshold = 10;
static int is_hdmi_mode = 0;
static int horz_active = 0;
static int vert_active = 0;
static int is_interlace = 0;
static int vfreq = 0;

static int audio_status = 0;
static int audio_sample_freq = 0;
static int audio_channel_alloc = 0;

struct aud_info_s{
    int real_sample_rate;
};

typedef struct hdmirx_dev_{
    struct cdev cdev;             /* The cdev structure */
    struct proc_dir_entry *proc_file;
    struct task_struct *task;
    struct aud_info_s aud_info;
    /**/
    unsigned int cur_width;
    unsigned int cur_height;
    unsigned int cur_frame_rate;
    unsigned char it660x_enable;
    unsigned char vdin_enable;
    unsigned char vdin_started;
    unsigned char task_pause;
    unsigned char global_event;
}hdmirx_dev_t;


static hdmirx_dev_t hdmirx_device;

static void start_vdin(int width, int height, int frame_rate, int field_flag);
static void stop_vdin(void);
/*****************************
*    hdmirx attr management :
******************************/

static ssize_t show_enable(struct device * dev, struct device_attribute *attr, char * buf)
{   
    return sprintf(buf, "%d\n", hdmirx_device.vdin_enable);
}
    
static ssize_t store_enable(struct device * dev, struct device_attribute *attr, const char * buf, size_t count)
{
    size_t r;
    int val;
    unsigned char vdin_enable;
    r = sscanf(buf, "%d", &val);
    if (r != 1) {
        return -EINVAL;
    }
    vdin_enable = val&0xff;
    hdmirx_device.global_event = (val>>8)&0xff;
    if(vdin_enable != hdmirx_device.vdin_enable){
        hdmirx_device.vdin_enable = vdin_enable; 
        if(hdmirx_device.vdin_enable == 1){
            start_vdin(getHDMIRXHorzActive(), getHDMIRXVertActive(), 10000, IsHDMIRXInterlace());
        }
        else if(hdmirx_device.vdin_enable == 0){
            stop_vdin();
        }  
    }

    return count;
}


static ssize_t show_poweron(struct device * dev, struct device_attribute *attr, char * buf)
{   
    return sprintf(buf, "%d\n", hdmirx_device.it660x_enable);
}
    
static ssize_t store_poweron(struct device * dev, struct device_attribute *attr, const char * buf, size_t count)
{
    size_t r;
    int val;
    r = sscanf(buf, "%d", &val);
    if (r != 1) {
        return -EINVAL;
    }
    if(val != hdmirx_device.it660x_enable){
        hdmirx_device.it660x_enable = val; 
        if(hdmirx_device.vdin_enable == 1){
        }
        else if(hdmirx_device.it660x_enable == 0){
        }  
    }

    return count;
}

#ifdef DEBUG_DVIN  
int hs_pol_inv;           
int vs_pol_inv;           
int de_pol_inv;           
int field_pol_inv;        
int ext_field_sel;        
int de_mode;              
int data_comp_map;        
int mode_422to444;        
int dvin_clk_inv;         
int vs_hs_tim_ctrl;       
int hs_lead_vs_odd_min;   
int hs_lead_vs_odd_max;   
int active_start_pix_fe;  
int active_start_pix_fo;  
int active_start_line_fe; 
int active_start_line_fo; 
int line_width;           
int field_height;        
#endif
    
static ssize_t store_dbg(struct device * dev, struct device_attribute *attr, const char * buf, size_t count)
{
    char tmpbuf[128];
    int i=0;
    unsigned int adr;
    unsigned int value=0;
    while((buf[i])&&(buf[i]!=',')&&(buf[i]!=' ')){
        tmpbuf[i]=buf[i];
        i++;
    }
    tmpbuf[i]=0;
    if(strncmp(tmpbuf, "config_dvin", 11)==0){
#ifdef DEBUG_DVIN  
        config_dvin (hs_pol_inv,          
                  vs_pol_inv,          
                  de_pol_inv,          
                  field_pol_inv,       
                  ext_field_sel,       
                  de_mode,             
                  data_comp_map,       
                  mode_422to444,       
                  dvin_clk_inv,        
                  vs_hs_tim_ctrl,      
                  hs_lead_vs_odd_min,  
                  hs_lead_vs_odd_max,  
                  active_start_pix_fe, 
                  active_start_pix_fo, 
                  active_start_line_fe,
                  active_start_line_fo,
                  line_width,          
                  field_height);       
#endif
    }
    else if(strncmp(tmpbuf, "pause", 5)==0){
        hdmirx_device.task_pause = 1;
        printk("Pause %s\n", __func__);
    }
    else if(strncmp(tmpbuf, "start", 5)==0){
        hdmirx_device.task_pause = 0;
        printk("Start %s\n", __func__);
    }
    else if(strncmp(tmpbuf, "spdif", 5)==0){
        setHDMIRX_SPDIFOutput();
    }
    else if(strncmp(tmpbuf, "i2s", 3)==0){
        setHDMIRX_I2SOutput(0x1);
    }
    else if(strncmp(tmpbuf, "hpd", 3)==0){
        if(tmpbuf[3]=='0'){
            CLEAR_HPD;
        }
        else if(tmpbuf[3]=='1'){
            SET_HPD;
        }
    }
    else if(tmpbuf[0]=='w'){
        adr=simple_strtoul(tmpbuf+2, NULL, 16);
        value=simple_strtoul(buf+i+1, NULL, 16);
        if(buf[1]=='h'){
            HDMIRX_WriteI2C_Byte(adr, value);
        }
        else if(buf[1]=='c'){
            WRITE_MPEG_REG(adr, value);
            pr_info("write %x to CBUS reg[%x]\n",value,adr);
        }
        else if(buf[1]=='p'){
            WRITE_APB_REG(adr, value);
            pr_info("write %x to APB reg[%x]\n",value,adr);
        }
    }
    else if(tmpbuf[0]=='r'){
        adr=simple_strtoul(tmpbuf+2, NULL, 16);
        if(buf[1]=='h'){
            value = HDMIRX_ReadI2C_Byte(adr);
            pr_info("HDMI reg[%x]=%x\n", adr, value);
        }
        else if(buf[1]=='c'){
            value = READ_MPEG_REG(adr);
            pr_info("CBUS reg[%x]=%x\n", adr, value);
        }
        else if(buf[1]=='p'){
            value = READ_APB_REG(adr);
            pr_info("APB reg[%x]=%x\n", adr, value);
        }
    }

    return 16;    
}

static DEVICE_ATTR(enable, S_IWUSR | S_IRUGO, show_enable, store_enable);
static DEVICE_ATTR(poweron, S_IWUSR | S_IRUGO, show_poweron, store_poweron);
static DEVICE_ATTR(debug, S_IRWXUGO, NULL, store_dbg);

/******************************
*  hdmirx kernel task
*******************************/
#define DUMP_TIME 20

#define PAD_GPIOD_4  99
#define PAD_GPIOD_6  101

BOOL ReadRXIntPin(void);

void InitHDMIRX(BOOL bFullInit);
BOOL CheckHDMIRX(void);
void Initial8051Timer1(void);
void InitUrt(void);
int dump_vidmode(void);
int dump_audSts(void);
void dump_InfoFrame(void);
/////////////////////////////////////////////////////
// Global Data
/////////////////////////////////////////////////////
int xCntSum, xCntCnt ;

BOOL ReadRXIntPin(void)
{
#if 0	
	bit i;

	i=P3_2;
	if(i==0)return TRUE;
	else return FALSE;
#endif
   return TRUE;
}

void MCU_init(void)
{
    ENABLE_HPD_MUX; // HPD
    CLEAR_HPD; 
    //ENABLE_SYSRSTN_MUX; // SYSRSTN, low to reset
    //RESET_SYSRSTN; //low to reset
}

void HoldSystem(void)
{
  while(!hdmirx_device.it660x_enable){
    msleep(10);
	}
}

BOOL RXHPD_ENABLE=TRUE ;
ULONG HPDOff_TickCount ;
#define HPDOFF_MIN_PERIOD 2000

// PIN89 (SYSRSTN): GPIOD_6

USHORT CalTimer(ULONG SetupCnt)
{
    ULONG ucTickCount = jiffies * 1000 / HZ;
    if(SetupCnt>ucTickCount)
    {
        return (0xffff-(SetupCnt-ucTickCount));
    }
    else
    {
        return (ucTickCount-SetupCnt);
    }
}

void hdmirx_set_hpd()
{
    if( RXHPD_ENABLE == FALSE )
    {
        while(CalTimer(HPDOff_TickCount)<HPDOFF_MIN_PERIOD)
        {
            msleep(100);
            //HDMIRX_DEBUG_PRINTF(("HPDOff_TickCount = %d, ucTickCount = %d\r",HPDOff_TickCount,ucTickCount)) ;
        }
        //HDMIRX_DEBUG_PRINTF(("\n")) ;

    	Turn_HDMIRX(ON) ;
        SET_HPD; //RX_HPD = HIGH ; // GPIOD_4    
        RXHPD_ENABLE = TRUE ;
    }
}

void hdmirx_clear_hpd()
{
    if( RXHPD_ENABLE == TRUE )
    {
      HPDOff_TickCount = jiffies * 1000 / HZ  ;
    	Turn_HDMIRX(OFF) ;
        CLEAR_HPD; //RX_HPD = LOW ;// GPIOD_4    
        RXHPD_ENABLE = FALSE ;
    }
}

static void update_status(unsigned char clear)
{
    static int xcntcnt, xcntsum;
    if(clear){
        is_hdmi_mode = 0;
        horz_active = 0;
        vert_active = 0;
        is_interlace = 0;
        vfreq = 0;
        
        audio_status = 0;
        audio_sample_freq = 0;
        audio_channel_alloc = 0;
        xcntcnt = 0;
        xcntsum = 0;
    }
    else{
        ULONG PCLK, HFreq;
        unsigned char sample_freq_idx, valid_ch;
        is_hdmi_mode = IsHDMIRXHDMIMode();
        horz_active = getHDMIRXHorzActive();
        vert_active = getHDMIRXVertActive();
        is_interlace = IsHDMIRXInterlace();

        xcntcnt ++ ;
        xcntsum += getHDMIRXxCnt() ;
        if( xcntcnt > 40 )
        {
            xcntcnt /= 2 ;
            xcntsum /= 2 ;
        }
        PCLK = 27000L * 128;
        PCLK *= (ULONG) xcntcnt ;
        PCLK /= (ULONG) xcntsum ;
        PCLK *= 1000L ; // 100*PCLK ;

        HFreq = PCLK / (ULONG)getHDMIRXHorzTotal() ; // HFreq
        vfreq = (HFreq*100) / (ULONG)getHDMIRXVertTotal() ; // VFreq * 100

        if(is_hdmi_mode!=0){
            audio_status = getHDMIRXAudioStatus();
            getHDMIRXAudioInfo(&sample_freq_idx, &valid_ch);
            audio_channel_alloc = valid_ch;
            switch(sample_freq_idx){
                case 0x0:
                    audio_sample_freq = 44100;
                    break;
                case 0x2:
                    audio_sample_freq = 48000;
                    break;
                case 0x3:
                    audio_sample_freq = 32000;
                    break;
                case 0x8:
                    audio_sample_freq = 88200;
                    break;
                case 0xa:
                    audio_sample_freq = 96000;
                    break;
                case 0xc:
                    audio_sample_freq = 176400;
                    break;
                case 0xe:
                    audio_sample_freq = 192000;
                    break;
                case 0x9:    
                    printk("smaple freq for HBR\n");
                    audio_sample_freq = 768000;
                    break;                        
            }
            if((audio_sample_freq != hdmirx_device.aud_info.real_sample_rate)||
                (hdmirx_device.global_event&0x1)){
                hdmirx_device.aud_info.real_sample_rate = audio_sample_freq;                    
#ifdef CONFIG_AML_AUDIO_DSP
                if(hdmirx_device.vdin_started){
                    mailbox_send_audiodsp(1, M2B_IRQ0_DSP_AUDIO_EFFECT, DSP_CMD_SET_HDMI_SR, (char *)&hdmirx_device.aud_info.real_sample_rate,sizeof(hdmirx_device.aud_info.real_sample_rate));
                    hdmirx_device.global_event&=(~0x1);
                    printk("[IT660x]%s: mailbox_send_audiodsp %d\n",__func__, hdmirx_device.aud_info.real_sample_rate);
                }
#endif
            }
        }
        else{
            audio_status = 0;
            audio_sample_freq = 0;
            audio_channel_alloc = 0;
        }
    }    
}    

static int 
hdmi_task_handle(void *data) 
{
    static BOOL bSignal ;
    BOOL bOldSignal, bChangeMode ;
    int dump_count = 0 ;
    int stable_count = 0;

    MCU_init() ;
	  printk("\n%s\n" , VERSION_STRING);
    while(1){
    	  HoldSystem();
        hdmirx_clear_hpd();
#ifdef _COPY_EDID_
        CopyDefaultEDID() ;
#endif

    	  InitHDMIRX(TRUE);
    	  hdmirx_set_hpd();
    
        xCntCnt = 0 ;
        xCntSum = 0 ;

        while(hdmirx_device.it660x_enable){
            while(hdmirx_device.task_pause){
                msleep(10);
            }

            if(ReadRXIntPin())
            {
                Check_HDMInterrupt();
            }
            //if(IsTimeOut(20)){
            dump_count ++ ;
    
            bOldSignal = bSignal ;
            bSignal = CheckHDMIRX();
            bChangeMode = (bSignal != bOldSignal);
    
            if(bChangeMode)
            {
                // if Changed Mode ...
                if(bSignal)
                {
                    stable_count = 0;
                    update_status(0);
            
                    // if signal is TRUE , then ...
                    dump_vidmode();
                    if( IsHDMIRXHDMIMode() ) dump_InfoFrame() ;
                    dump_audSts();
                }
                else
                {
                    stable_count = 0;
                    stop_vdin();
                    update_status(1);
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
                    if(stable_count<stable_threshold){
                        stable_count++;
                        if(stable_count == stable_threshold){
                            start_vdin(getHDMIRXHorzActive(), getHDMIRXVertActive(), 10000, IsHDMIRXInterlace());
                        }
                    }

                    update_status(0);
                    
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
                    stable_count = 0;
                    stop_vdin();
                    update_status(1);
                    
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
                    printk("Reg10 = %02X\nReg12 = %02X\nReg64 = %02X\nReg65 = %02X\n"
                    ,(int)HDMIRX_ReadI2C_Byte(0x10)
                    ,(int)HDMIRX_ReadI2C_Byte(0x12)
                    ,(int)HDMIRX_ReadI2C_Byte(0x64)
                    ,(int)HDMIRX_ReadI2C_Byte(0x65) ) ;
                }
                printk("\n\n") ;
                DumpHDMIRXReg();
            }
            //}//	if(IsTimeOut(20))
            msleep(10);
    
        }
        PowerDownHDMI();
    }
    return 0;

}

int dump_vidmode(void)
{
    USHORT HActive, VActive ;
    USHORT HTotal, VTotal ;
    ULONG HFreq, VFreq ;
    ULONG PCLK ;
    if((it660x_debug_flag&0x1)==0){
        return 0;
    }
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


	printk("\n========================================================================\n") ;
	printk("%s mode\n",IsHDMIRXHDMIMode()?"HDMI":"DVI") ;
    printk("Mode - %dx%d@",HActive,VActive);
    printk("%ld.%02ldHz",VFreq/100,VFreq%100) ;
    switch(getHDMIRXOutputColorDepth())
    {
    case 0x7: printk("@48bits") ; break ;
    case 0x6: printk("@36bits") ; break ;
    case 0x5: printk("@30bits") ; break ;
    case 0x4: printk("@24bits") ; break ;
    default: printk("@No def(24bits)") ; break ;
    }
    printk(", PCLK = %ld.%02ldMHz", PCLK/1000000, (PCLK/10000)%100) ;
    PCLK = xCntSum ;
    PCLK *= 100 ;
    PCLK /= xCntCnt ;
    PCLK -= (ULONG)(xCntSum / xCntCnt)*100 ;
    printk(",xCnt= %d.%02ld\n", xCntSum/xCntCnt,PCLK) ;

    printk("<%4dx%4d>,",HTotal,VTotal);

    printk("H:(%d,%d,%d),"
		,getHDMIRXHorzFrontPorch()
	    ,getHDMIRXHorzSyncWidth()
	    ,getHDMIRXHorzBackPorch());

    printk("V:(%d,%d,%d), "
		,getHDMIRXVertFrontPorch()
	    ,getHDMIRXVertSyncWidth()
	    ,getHDMIRXVertSyncBackPorch());

    printk("VSyncToDE = %d\n",getHDMIRXVertSyncToDE());
	printk("========================================================================\n") ;
    printk("HDCP %s\n",IsHDCPOn()?"ON":"OFF") ;
	printk("========================================================================\n") ;
	return 0;
}

int dump_audSts(void)
{
    BYTE audio_status ;
    if((it660x_debug_flag&0x1)==0){
        return 0;
    }

	printk("\n========================================================================\n") ;
    audio_status = getHDMIRXAudioStatus() ;
    if( (audio_status & T_AUDIO_MASK)!=T_AUDIO_OFF )
    {
        BYTE ch[5] ;
        if( audio_status == T_AUDIO_HBR )
        {
            printk("Audio input is HBR (High Bit Rate) audio.\n") ;
        }
        else if( audio_status == T_AUDIO_DSD )
        {
            printk("Audio input is DSD (One Bit Audio) audio.\n") ;
        }
        else
        {
            if( audio_status & T_AUDIO_NLPCM )
            {
                printk("Audio input is IEC 61937 compressed audio.\n") ;
            }
            else
            {
                printk("Audio input is IEC 60958 linear PCM audio.\n") ;
            }


            printk("layout %d, ",(audio_status & F_AUDIO_LAYOUT_1)?1:0) ;
            printk("%d source\n", (USHORT)audio_status & 7) ;

            getHDMIRXAudioChannelStatus(ch) ;
            printk("Channel Status: %02X %02X %02X %02X %02X\n",(int)ch[0],(int)ch[1],(int)ch[2],(int)ch[3],(int)ch[4]) ;


        }
    }
    else
    {
        printk("No Audio.\n") ;
    }
	printk("========================================================================\n") ;
	return 0;
}

void
dump_InfoFrame(void)
{
    BYTE INFOFRAME[31] ;
    int i ;
    if((it660x_debug_flag&0x1)==0){
        return 0;
    }


    if( GetAVIInfoFrame(INFOFRAME) )
    {
        printk("GetAVIInfoFrame():") ;
        for( i = 0 ; i <= (3+(INFOFRAME[2] & 0x1F)) ; i++ )
        {
            printk(" %02X",(int)INFOFRAME[i]) ;
        }
        printk("\n") ;
    }
    else
    {
        printk("Cannot get AVI Infoframe()\n") ;
    }

    if( GetAudioInfoFrame(INFOFRAME) )
    {
        printk("GetAudioInfoFrame():") ;
        for( i = 0 ; i <= (3+(INFOFRAME[2] & 0x1F)) ; i++ )
        {
            printk(" %02X",(int)INFOFRAME[i]) ;
        }
        printk("\n") ;
    }
    else
    {
        printk("Cannot get audio infoframe.\n") ;
    }


    if( GetVENDORSPECInfoFrame(INFOFRAME) )
    {
        printk("GetVENDORSPECInfoFrame():") ;
        for( i = 0 ; i <= (3+(INFOFRAME[2] & 0x1F)) ; i++ )
        {
            printk(" %02X",(int)INFOFRAME[i]) ;
        }
        printk("\n") ;
    }
    else
    {
        printk("Cannot GetVENDORSPECInfoFrame()\n") ;
    }
}

static void stop_vdin(void)
{
    if(hdmirx_device.vdin_started){
        stop_tvin_service(0);
        hdmirx_device.vdin_started=0;
        printk("%s: stop vdin\n", __func__);
    }
}

static void start_vdin(int width, int height, int frame_rate, int field_flag)
{
    tvin_parm_t para;
    if(hdmirx_device.vdin_enable == 0){
        return;
    }    
    if(hdmirx_device.vdin_started){
        if(hdmirx_device.cur_width != width ||
                hdmirx_device.cur_height != height ||
                hdmirx_device.cur_frame_rate != frame_rate){
            stop_tvin_service(0);
            hdmirx_device.vdin_started=0;
            printk("%s: stop vdin\n", __func__);
        }
    }
    
    if(hdmirx_device.vdin_started==0 && width>0 && height>0 && frame_rate >0){
        hdmirx_device.cur_width = width;
        hdmirx_device.cur_height = height;
        hdmirx_device.cur_frame_rate = frame_rate;
        
#ifdef DEBUG_DVIN  
        hs_pol_inv = 0;
        vs_pol_inv = height>480?0:1;          
        de_pol_inv = 0;          
        field_pol_inv = 0;       
        ext_field_sel = 0;       
        de_mode = 0;             
        data_comp_map = 0;       
        mode_422to444 = 0;       
        dvin_clk_inv = 0;        
        vs_hs_tim_ctrl = 0;      
        hs_lead_vs_odd_min = 0;  
        hs_lead_vs_odd_max = 0;  
        active_start_pix_fe = getHDMIRXHorzBackPorch(); 
        active_start_pix_fo = getHDMIRXHorzBackPorch(); 
        active_start_line_fe = getHDMIRXVertSyncBackPorch();
        active_start_line_fo = getHDMIRXVertSyncBackPorch();
        line_width = getHDMIRXHorzTotal();          
        field_height = getHDMIRXVertTotal();
#endif
        if(field_flag && height <= 480 ){
            config_dvin(0, //hs_pol_inv,          
                      1, //vs_pol_inv,          
                      0, //de_pol_inv,          
                      0, //field_pol_inv,       
                      0, //ext_field_sel,       
                      2, //de_mode,             
                      0, //data_comp_map,       
                      0, //mode_422to444,       
                      0, //dvin_clk_inv,        
                      0, //vs_hs_tim_ctrl,      
                      400, //hs_lead_vs_odd_min,  
                      1200, //hs_lead_vs_odd_max,  
                      getHDMIRXHorzBackPorch(),//0xdc, //active_start_pix_fe, 
                      getHDMIRXHorzBackPorch(),//0xdc, //active_start_pix_fo, 
                      getHDMIRXVertSyncBackPorch(), //0x19, //active_start_line_fe,
                      getHDMIRXVertSyncBackPorch(),//0x19, //active_start_line_fo,
                      getHDMIRXHorzTotal(), //0x672, //line_width,          
                      getHDMIRXVertTotal() //0x2ee //field_height
                      );       
        }
        else{
            config_dvin(0, //hs_pol_inv,          
                      height>480?0:1, //vs_pol_inv,          
                      0, //de_pol_inv,          
                      0, //field_pol_inv,       
                      0, //ext_field_sel,       
                      0, //de_mode,             
                      0, //data_comp_map,       
                      0, //mode_422to444,       
                      0, //dvin_clk_inv,        
                      0, //vs_hs_tim_ctrl,      
                      0, //hs_lead_vs_odd_min,  
                      0, //hs_lead_vs_odd_max,  
                      getHDMIRXHorzBackPorch(),//0xdc, //active_start_pix_fe, 
                      getHDMIRXHorzBackPorch(),//0xdc, //active_start_pix_fo, 
                      getHDMIRXVertSyncBackPorch(), //0x19, //active_start_line_fe,
                      getHDMIRXVertSyncBackPorch(),//0x19, //active_start_line_fo,
                      getHDMIRXHorzTotal(), //0x672, //line_width,          
                      getHDMIRXVertTotal() //0x2ee //field_height
                      );       
        }        
        para.h_active = hdmirx_device.cur_width;
        para.v_active = hdmirx_device.cur_height;
        para.port  = TVIN_PORT_DVIN0;
        if(field_flag){
            para.v_active <<= 1;
            //if(height == 1080){
                para.fmt = TVIN_SIG_FMT_HDMI_1920x1080I_60HZ;
                para.scan_mode = TVIN_SCAN_MODE_PROGRESSIVE;
            //}
            //else{
            //    para.fmt_info.fmt = TVIN_SIG_FMT_HDMI_1440x480I_60Hz;
            //}
        }
        else{
            para.fmt = TVIN_SIG_FMT_MAX+1;//TVIN_SIG_FMT_MAX+1;TVIN_SIG_FMT_CAMERA_1280X720P_30Hz
            para.scan_mode = TVIN_SCAN_MODE_INTERLACED;
        }
        para.frame_rate = frame_rate;
        para.cfmt = TVIN_YUV422;
        para.hsync_phase = 1;
      	para.vsync_phase = 0;	
        start_tvin_service(0,&para);
        hdmirx_device.vdin_started = 1;
        
        printk("%s: %dx%d %d/s\n", __func__, width, height, frame_rate);
        
        hdmirx_device.aud_info.real_sample_rate = audio_sample_freq;                    
#ifdef CONFIG_AML_AUDIO_DSP
        mailbox_send_audiodsp(1, M2B_IRQ0_DSP_AUDIO_EFFECT, DSP_CMD_SET_HDMI_SR, (char *)&hdmirx_device.aud_info.real_sample_rate,sizeof(hdmirx_device.aud_info.real_sample_rate));
        printk("[IT660x]%s: mailbox_send_audiodsp %d\n",__func__, hdmirx_device.aud_info.real_sample_rate);
#endif
        
    }
}


/*****************************
*    hdmirx driver file_operations 
*    
******************************/
static int it660x_hdmirx_open(struct inode *node, struct file *file)
{
    hdmirx_dev_t *hdmirx_in_devp;

    /* Get the per-device structure that contains this cdev */
    hdmirx_in_devp = container_of(node->i_cdev, hdmirx_dev_t, cdev);
    file->private_data = hdmirx_in_devp;

    return 0;

}


static int it660x_hdmirx_release(struct inode *node, struct file *file)
{
    //hdmirx_dev_t *hdmirx_in_devp = file->private_data;

    /* Reset file pointer */

    /* Release some other fields */
    /* ... */
    return 0;
}



static int it660x_hdmirx_ioctl(struct inode *node, struct file *file, unsigned int cmd,   unsigned long args)
{
    int   r = 0;
    switch (cmd) {
        default:
            break;
    }
    return r;
}

const static struct file_operations it660x_hdmirx_fops = {
    .owner    = THIS_MODULE,
    .open     = it660x_hdmirx_open,
    .release  = it660x_hdmirx_release,
//    .ioctl    = it660x_hdmirx_ioctl,
};

int it660xin_init(void);
int it660xin_remove(void);

static int it660x_hdmirx_probe(struct platform_device *pdev)
{
    int r;
    HDMI_DEBUG();
    pr_dbg("it660x_hdmirx_probe\n");

    //it660xin_init();



    r = alloc_chrdev_region(&hdmirx_id, 0, HDMI_RX_COUNT, DEVICE_NAME);
    if (r < 0) {
        pr_error("Can't register major for it660x_hdmirx device\n");
        return r;
    }
    hdmirx_class = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(hdmirx_class))
    {
        unregister_chrdev_region(hdmirx_id, HDMI_RX_COUNT);
        return -1;
        //return PTR_ERR(aoe_class);
    }

    cdev_init(&(hdmirx_device.cdev), &it660x_hdmirx_fops);
    hdmirx_device.cdev.owner = THIS_MODULE;
    cdev_add(&(hdmirx_device.cdev), hdmirx_id, HDMI_RX_COUNT);

    //hdmirx_dev = device_create(hdmirx_class, NULL, hdmirx_id, "it660x_hdmirx%d", 0);
    hdmirx_dev = device_create(hdmirx_class, NULL, hdmirx_id, NULL, "it660x_hdmirx%d", 0); //kernel>=2.6.27 

    device_create_file(hdmirx_dev, &dev_attr_enable);
    device_create_file(hdmirx_dev, &dev_attr_poweron);
    device_create_file(hdmirx_dev, &dev_attr_debug);
    
    if (hdmirx_dev == NULL) {
        pr_error("device_create create error\n");
        class_destroy(hdmirx_class);
        r = -EEXIST;
        return r;
    }
    hdmirx_device.task = kthread_run(hdmi_task_handle, &hdmirx_device, "kthread_hdmi");
    
	if (r < 0){
		printk(KERN_ERR "hdmirx: register switch dev failed\n");
		return r;
	}    

    return r;
}

static int it660x_hdmirx_remove(struct platform_device *pdev)
{
    kthread_stop(hdmirx_device.task);
    
    //it660xin_remove();
    /* Remove the cdev */
    device_remove_file(hdmirx_dev, &dev_attr_enable);
    device_remove_file(hdmirx_dev, &dev_attr_poweron);
    device_remove_file(hdmirx_dev, &dev_attr_debug);

    cdev_del(&hdmirx_device.cdev);

    device_destroy(hdmirx_class, hdmirx_id);

    class_destroy(hdmirx_class);

    unregister_chrdev_region(hdmirx_id, HDMI_RX_COUNT);
    return 0;
}

#ifdef CONFIG_PM
static int it660x_hdmirx_suspend(struct platform_device *pdev,pm_message_t state)
{
    pr_info("it660x_hdmirx: hdmirx_suspend\n");
    return 0;
}

static int it660x_hdmirx_resume(struct platform_device *pdev)
{
    pr_info("it660x_hdmirx: resume module\n");
    return 0;
}

static struct platform_driver it660x_hdmirx_driver = {
    .probe      = it660x_hdmirx_probe,
    .remove     = it660x_hdmirx_remove,
#ifdef CONFIG_PM
    .suspend    = it660x_hdmirx_suspend,
    .resume     = it660x_hdmirx_resume,
#endif
    .driver     = {
        .name   = DEVICE_NAME,
		    .owner	= THIS_MODULE,
    }
};

static struct platform_device* it660x_hdmirx_device = NULL;


static int  __init it660x_hdmirx_init(void)
{
    pr_dbg("it660x_hdmirx_init\n");
    memset(&hdmirx_device, 0, sizeof(hdmirx_device));
	  it660x_hdmirx_device = platform_device_alloc(DEVICE_NAME,0);
    if (!it660x_hdmirx_device) {
        pr_error("failed to alloc it660x_hdmirx_device\n");
        return -ENOMEM;
    }
    
    if(platform_device_add(it660x_hdmirx_device)){
        platform_device_put(it660x_hdmirx_device);
        pr_error("failed to add it660x_hdmirx_device\n");
        return -ENODEV;
    }
    if (platform_driver_register(&it660x_hdmirx_driver)) {
        pr_error("failed to register it660x_hdmirx module\n");
        
        platform_device_del(it660x_hdmirx_device);
        platform_device_put(it660x_hdmirx_device);
        return -ENODEV;
    }
    return 0;
}




static void __exit it660x_hdmirx_exit(void)
{
    pr_dbg("it660x_hdmirx_exit\n");
    platform_driver_unregister(&it660x_hdmirx_driver);
    platform_device_unregister(it660x_hdmirx_device); 
    it660x_hdmirx_device = NULL;
    return ;
}

module_init(it660x_hdmirx_init);
module_exit(it660x_hdmirx_exit);

MODULE_PARM_DESC(it660x_debug_flag, "\n it660x_debug_flag \n");
module_param(it660x_debug_flag, int, 0664);

MODULE_PARM_DESC(stable_threshold, "\n stable_threshold \n");
module_param(stable_threshold, int, 0664);

MODULE_PARM_DESC(is_hdmi_mode, "\n is_hdmi_mode \n");
module_param(is_hdmi_mode, int, 0664);

MODULE_PARM_DESC(horz_active, "\n horz_active \n");
module_param(horz_active, int, 0664);

MODULE_PARM_DESC(vert_active, "\n vert_active \n");
module_param(vert_active, int, 0664);

MODULE_PARM_DESC(is_interlace, "\n is_interlace \n");
module_param(is_interlace, int, 0664);

MODULE_PARM_DESC(vfreq, "\n vfreq \n");
module_param(vfreq, int, 0664);

MODULE_PARM_DESC(audio_status, "\n audio_status \n");
module_param(audio_status, int, 0664);

MODULE_PARM_DESC(audio_sample_freq, "\n audio_sample_freq \n");
module_param(audio_sample_freq, int, 0664);

MODULE_PARM_DESC(audio_channel_alloc, "\n audio_channel_alloc \n");
module_param(audio_channel_alloc, int, 0664);


#ifdef DEBUG_DVIN  
MODULE_PARM_DESC(hs_pol_inv, "\n hs_pol_inv \n");
module_param(hs_pol_inv, int, 0664);

MODULE_PARM_DESC(vs_pol_inv, "\n vs_pol_inv \n");
module_param(vs_pol_inv, int, 0664);
          
MODULE_PARM_DESC(de_pol_inv, "\n de_pol_inv \n");
module_param(de_pol_inv, int, 0664);

MODULE_PARM_DESC(field_pol_inv, "\n field_pol_inv \n");
module_param(field_pol_inv, int, 0664);

MODULE_PARM_DESC(ext_field_sel, "\n ext_field_sel \n");
module_param(ext_field_sel, int, 0664);
           
MODULE_PARM_DESC(de_mode, "\n de_mode \n");
module_param(de_mode, int, 0664);
      
MODULE_PARM_DESC(data_comp_map, "\n data_comp_map \n");
module_param(data_comp_map, int, 0664);
       
MODULE_PARM_DESC(mode_422to444, "\n mode_422to444 \n");
module_param(mode_422to444, int, 0664);
         
MODULE_PARM_DESC(dvin_clk_inv, "\n dvin_clk_inv \n");
module_param(dvin_clk_inv, int, 0664);
      
MODULE_PARM_DESC(vs_hs_tim_ctrl, "\n vs_hs_tim_ctrl \n");
module_param(vs_hs_tim_ctrl, int, 0664);

MODULE_PARM_DESC(hs_lead_vs_odd_min, "\n hs_lead_vs_odd_min \n");
module_param(hs_lead_vs_odd_min, int, 0664);

MODULE_PARM_DESC(hs_lead_vs_odd_max, "\n hs_lead_vs_odd_max \n");
module_param(hs_lead_vs_odd_max, int, 0664);
  
MODULE_PARM_DESC(active_start_pix_fe, "\n active_start_pix_fe \n");
module_param(active_start_pix_fe, int, 0664);
 
MODULE_PARM_DESC(active_start_pix_fo, "\n active_start_pix_fo \n");
module_param(active_start_pix_fo, int, 0664);

MODULE_PARM_DESC(active_start_line_fe, "\n active_start_line_fe \n");
module_param(active_start_line_fe, int, 0664);

MODULE_PARM_DESC(active_start_line_fo, "\n active_start_line_fo \n");
module_param(active_start_line_fo, int, 0664);
           
MODULE_PARM_DESC(line_width, "\n line_width \n");
module_param(line_width, int, 0664);
      
MODULE_PARM_DESC(field_height, "\n field_height \n");
module_param(field_height, int, 0664);
#endif

MODULE_DESCRIPTION("IT660X HDMI RX driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0.0");


#endif
