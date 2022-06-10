obj-m := moduleA.o moduleB.o

CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
install:
	@insmod moduleA.ko
	@insmod moduleB.ko
uninstall:
	@rmmod moduleB moduleA
	dmesg | tail -n 10