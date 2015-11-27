#ifndef __IT6604_H__
#define __IT6604_H__

#include <linux/ioctl.h>
//#include "hi_type.h"


#define IT6604_NTSC	        1
#define IT6604_PAL	        2
#define IT6604_AUTO	        3
#define IT6604_INVALID_MODE	4

typedef struct _it6604_video_norm
{
    unsigned int chip;
    unsigned int mode;
} it6604_video_norm;


#define IT6604_1D1_MODE     0
#define IT6604_2D1_MODE     1
#define IT6604_4CIF_MODE    2
#define IT6604_4D1_MODE     3

typedef struct _it6604_work_mode
{
    unsigned int chip;
    unsigned int mode;
} it6604_work_mode;


typedef struct _it6604_video_loss
{
    unsigned int chip;
    unsigned int ch;
    unsigned int is_lost;
} it6604_video_loss;


#define IT6604_SET_HUE          0x01
#define IT6604_SET_CONTRAST     0x02
#define IT6604_SET_BRIGHT       0x04
#define IT6604_SET_SATURATION   0x08

typedef struct _it6604_image_adjust
{
    unsigned char chip;
    unsigned char chn;
	unsigned char hue;
	unsigned char contrast;
	unsigned char brightness;
	unsigned char saturation;
	unsigned long item_sel;/* use such as "IT6604_SET_HUE|IT6604_SET_CONTRAST" */
} it6604_image_adjust;


#define IT6604_IOC_MAGIC            't'

#define IT6604CMD_READ_REG		      _IOWR(IT6604_IOC_MAGIC, 1, int) 
#define IT6604CMD_WRITE_REG	        _IOW(IT6604_IOC_MAGIC, 2, int) 

#define IT6604_GET_VIDEO_LOSS		    _IOWR(IT6604_IOC_MAGIC, 4, it6604_video_loss) 
#define IT6604_SET_IMAGE_ADJUST	    _IOW(IT6604_IOC_MAGIC, 5, it6604_image_adjust) 
#define IT6604_GET_IMAGE_ADJUST	    _IOWR(IT6604_IOC_MAGIC, 6, it6604_image_adjust) 
#define IT6604_SET_VIDEO_NORM	      _IOW(IT6604_IOC_MAGIC, 7, it6604_video_norm) 
#define IT6604_GET_VIDEO_NORM	      _IOWR(IT6604_IOC_MAGIC, 8, it6604_video_norm) 
#define IT6604_SET_WORK_MODE	      _IOW(IT6604_IOC_MAGIC, 9, it6604_work_mode) 


unsigned char tbl_pal_tw2865_8KHz[] = {  
	0x83,0xB5,0x09,0x00,0xA0,0x00			//...0xF0~0xF5
};
unsigned char tbl_ntsc_tw2865_8KHz[] = {  
	0x83,0xB5,0x09,0x78,0x85,0x00			//...0xF0~0xF5
  };
#endif


