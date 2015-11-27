
ifeq ($(PARAM_FILE), )
	PARAM_FILE:=../../Makefile.param
		include $(PARAM_FILE)
endif
obj-m += it6604.o
obj-m += hdmirx.o
#it6604-objs:it6604.o
# hdmirx.o
#it_6604-y += it6604.o

EXTRA_CFLAGS += -D$(HI_FPGA) 
#EXTRA_CFLAGS+=-I$(PWD)/../gpio-i2c -I$(PWD)/../gpio-i2c1
EXTRA_CFLAGS +=-I$(PWD)/../gpio-i2c_8b

default:
	make -C $(LINUX_ROOT) M=$(PWD) modules
clean: 
	@make -C $(LINUX_ROOT) M=$(PWD) clean



