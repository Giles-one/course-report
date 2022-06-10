.PHONY: all clean install unistall
obj-m += myWorkqueue.o

CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
install:
	@insmod myWorkqueue.ko && sleep 3
unistall:
	@rmmod myWorkqueue
	@dmesg | tail -n 20
	