/* it6604.c
author:9crk.com
you can not deliver or use this file in any condition!! 
 */


#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>



#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <linux/major.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h> 
#include <asm/uaccess.h>



#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <asm/uaccess.h>
//#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/system.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/list.h>
//#include <asm/semaphore.h>
#include <asm/delay.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/poll.h>
//#include <asm/hardware.h>
#include <asm/bitops.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <linux/moduleparam.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>

#include "gpio_i2c.h"
//#include "gpio_i2c1.h"

//#include "it6604_def.h"
#include "it6604.h"


static int norm = IT6604_PAL;

static int chips = 2;

#define IT6604A_I2C_ADDR 	0x90
#define IT6604B_I2C_ADDR 	0x92
#define IT6604C_I2C_ADDR 	0x52
#define IT6604D_I2C_ADDR 	0x56

#ifdef hi3515
unsigned char it6604_i2c_addr[] = {0x50, 0x52};
#else
unsigned char it6604_i2c_addr[] = { IT6604A_I2C_ADDR, 
                                    IT6604B_I2C_ADDR,
									};
#endif
/************************************************************************
zhouhua add this
************************************************************************/
#include "hdmirx.h"

void zhou_hdmi_init()
{
	BOOL bSignal, bChangeMode ;
	hdmirx_clear_hpd();
	InitHDMIRX(TRUE);
	hdmirx_set_hpd();
	Check_HDMInterrupt();
	bSignal = CheckHDMIRX();
	printk("CheckHDMIRx = %d\n",bSignal);
}
void zhou_hdmi_exit()
{
	PowerDownHDMI();
}
BYTE HDMIRX_ReadI2C_Byte(BYTE RegAddr);
SYS_STATUS HDMIRX_WriteI2C_Byte(BYTE RegAddr, BYTE Data);
SYS_STATUS HDMIRX_ReadI2C_ByteN(BYTE RegAddr, BYTE *pData, int N);
SYS_STATUS HDMIRX_WriteI2C_ByteN(BYTE RegAddr, BYTE *pData, int N);









/***********************************************************************
zhouhua end
***********************************************************************/
 
#define IT6604_I2C_ADDR(chip_id)    (it6604_i2c_addr[chip_id])
#define IT6604_INVALID_CHIPID(ChnNo) ((ChnNo) >= chips)

static unsigned char it6604_byte_write(unsigned char chip_addr,
										     unsigned char addr     , 
										     unsigned char data     ) 
{

#if 0

#ifndef HI_FPGA
    gpio_i2c_write(chip_addr,addr,data);
#else
   
    if (IT6604A_I2C_ADDR == chip_addr || IT6604B_I2C_ADDR == chip_addr)
    {
        gpio_i2c_write(chip_addr,addr,data);
    }
    else
    {
        gpio_i2c1_write(chip_addr,addr,data);
    }
    
#endif
#else
    gpio_i2c_write(chip_addr,addr,data);

#endif


	return 0;
}
SYS_STATUS HDMIRX_WriteI2C_Byte(BYTE RegAddr, BYTE Data)
{
	gpio_i2c_write(IT6604A_I2C_ADDR,RegAddr,Data);		
}
SYS_STATUS HDMIRX_WriteI2C_ByteN(BYTE RegAddr, BYTE *pData, int N)
{
	int i;
	for(i=0;i<N;i++){
		HDMIRX_WriteI2C_Byte(RegAddr+i, *(pData+i));
	}
	return 0;
}
static unsigned char it6604_byte_read(unsigned char chip_addr, unsigned char addr)
{

#if 0
#ifndef HI_FPGA
    return gpio_i2c_read(chip_addr,addr);
#else
    if (IT6604A_I2C_ADDR == chip_addr || IT6604B_I2C_ADDR == chip_addr)
    {
        return gpio_i2c_read(chip_addr,addr);
    }
    else
    {
        return gpio_i2c1_read(chip_addr,addr);
    }
#endif	

#else
    return gpio_i2c_read(chip_addr,addr);
#endif
}
BYTE HDMIRX_ReadI2C_Byte(BYTE RegAddr)
{
	return gpio_i2c_read(IT6604A_I2C_ADDR,RegAddr);
}
SYS_STATUS HDMIRX_ReadI2C_ByteN(BYTE RegAddr, BYTE *pData, int N)
{
	int i;
	for(i=0;i<N;i++){
		*(pData+i) = HDMIRX_ReadI2C_Byte(RegAddr+i);
	}
	return 0;
}
static void it6604_write_table(unsigned char chip_addr,
		unsigned char addr, unsigned char *tbl_ptr, unsigned char tbl_cnt)
{
	unsigned char i = 0;
	
	for(i = 0; i < tbl_cnt; i ++)
	{
		it6604_byte_write(chip_addr, (addr + i), *(tbl_ptr + i));
	}
}


int it6604_open(struct inode * inode, struct file * file)
{
	return 0;
} 

int it6604_close(struct inode * inode, struct file * file)
{
	return 0;
}


//int it6604_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
long it6604_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("IOCTRL OK!\n");
	return 0;
}



static void it6604_comm_init(unsigned char addr)
{
    unsigned char id = 0;
	int i;
	/*
	Initial Progress
1. Set HPD (HDMI Connection Pin19) to low (if possible).
2. Reg06 = 0x00 to power on all modules.
3. Reg07[3:2] = ‘11’ to turn off the termination.
4. Reg05 = 0x81
5. Reg16 = 0x0F
6. Reg17 = 0x07
7. Reg18 = 0x07
8. Reg8C = 0x20 (5~8 is for initial interrupt mask setting)
9. Load the default value.
	reg08 = 0xAE
	reg1D = 0x20
	reg3B=0x40
	reg68=0x03
	reg6B=0x11
	Reg6C=0x00
	Reg93=0x43
	Reg94=0x4F
	Reg95=0x87
	Reg96=0x33
10. Reset the HDCP ROM.
11. Configure the HDCP repeater setting
i) Receiver mode, reg73[7:4] = ‘0000’
ii) Repeater mode, reg73[7:4] = ‘1000’
12. Delay about 500ms to make sure the HPD off enough.
13. Reg07[3:2] = ‘00’
14. Set HPD to high (if possible).

*/

	//读取deviceID
    id = it6604_byte_read(addr, 0x02);//zhouhua read deviceID Low byte,should be 0x23
    if (0xff == id || 0x00 == id)
    {
        printk("warning: it6604 0x%x i2c_read err, val:0x%x!!!\n", addr, id);
        return;
    }
	//zhouhua power on all device
	it6604_byte_write(addr, 0x06, 0x00);
	it6604_byte_write(addr, 0x07, 0x0C);
	it6604_byte_write(addr, 0x05, 0x81);
	it6604_byte_write(addr, 0x16, 0x0F);
	it6604_byte_write(addr, 0x17, 0x07);
	it6604_byte_write(addr, 0x18, 0x07);
	it6604_byte_write(addr, 0x8C, 0x20);
	it6604_byte_write(addr, 0x08, 0xAE);
	it6604_byte_write(addr, 0x1D, 0x20);
	it6604_byte_write(addr, 0x3B, 0x40);
	it6604_byte_write(addr, 0x68, 0x03);
	it6604_byte_write(addr, 0x6B, 0x11);
	it6604_byte_write(addr, 0x6C, 0x00);
	it6604_byte_write(addr, 0x93, 0x43);
	it6604_byte_write(addr, 0x94, 0x4F);
	it6604_byte_write(addr, 0x95, 0x87);
	it6604_byte_write(addr, 0x96, 0x33);
	
	id = it6604_byte_read(addr, 0x9B) & ~(0xC0);
	for(i=0;i<16;i++){
		it6604_byte_write(addr, 0x9B, 0x80|id) ;
		it6604_byte_write(addr, 0x9B, 0xC0|id) ;
	}
	it6604_byte_write(addr, 0x9B,id) ;
	
	it6604_byte_write(addr, 0x73, 0x00);
	mdelay(600);
	it6604_byte_write(addr, 0x07, 0x00);
}


static struct file_operations it6604_fops = {
	.owner      = THIS_MODULE,
    .unlocked_ioctl  = it6604_ioctl,//在kernel 2.6.36 中已经完全删除了struct file_operations 中的ioctl 函数指针
	.open       = it6604_open,
	.release    = it6604_close
};

static struct miscdevice it6604_dev = {
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "it6604dev",
	.fops  		= &it6604_fops,
};


module_param(norm, uint, S_IRUGO);
module_param(chips, uint, S_IRUGO);


static int __init it6604_module_init(void)
{
	int ret = 0, i = 0;
    unsigned char i2c_addr;

	/* first check the parameters*/
	if ((norm != IT6604_PAL) && (norm != IT6604_NTSC))
	{
		printk("module param norm must be PAL(%d) or NTSC(%d)\n", IT6604_PAL ,IT6604_NTSC);
		return -1;
	}
    if (chips <= 0 || chips > 4)
    {
        printk("module param chip invalid value:%d\n", chips);
		return -1;
    }

	/* register misc device*/
	ret = misc_register(&it6604_dev);
	if (ret)
	{
		printk("ERROR: could not register it6604 devices\n");
		return ret;
	}
    
	/* initize each it6604*/
	for (i = 0; i < chips; i ++)
	{
        i2c_addr = it6604_i2c_addr[i];

		zhou_hdmi_init();
		//it6604_comm_init(i2c_addr);
        
        //it6604_video_init(i2c_addr, norm);
        
  //      it6604_audio_init(i2c_addr);
	}
    
    /* audio cascade */
  //  it6604_audio_cascade(chips);
	
	printk("it6604 driver init successful!\n");
	
	return 0;
}



static void __exit it6604_module_exit(void)
{
	zhou_hdmi_exit();
	misc_deregister(&it6604_dev);	
}

module_init(it6604_module_init);
module_exit(it6604_module_exit);

#ifdef MODULE
//#include <linux/compile.h>
#endif
MODULE_LICENSE("GPL");

