# this is the makefile for timer
DEBFLAGS = -O2

# variablen
#EXTRA_CFLAGS  = -Wall
#EXTRA_CFLAGS += $(DEBFLAGS)
#EXTRA_CFLAGS += -DDEBUG_MESSAGES
#EXTRA_CFLAGS += -I$(LDDINC)

ccflags-y := -O2 -DDEBUG_MESSAGES -Wall

MODULE=timer


# If KERNALRELEASE is defined, we've been invoked from the
# kernel build system and can use its language
ifneq ($(KERNELRELEASE),)
# call from kernel build system
    obj-m := $(MODULE).o

# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else

    KERNELDIR ?= /lib/modules/$(shell uname -r)/build
    PWD := $(shell pwd) 


modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

load:
	./timer.sh --load

unload:
	./timer.sh --unload


clean: 
	-rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers

clcvim:
	-rm -rf .*.swp .*~


