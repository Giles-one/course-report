.PHONY: all fs run clean
obj-m += chrdev_driver.o

CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
	@gcc -static -o test test.c
	@cp chrdev_driver.ko test fs/
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
	@rm initramfs.cpio test fs/test
fs:
	@cd fs && find . -print0 | cpio --null -ov --format=newc > ../initramfs.cpio
run:
	@qemu-system-x86_64 \
	  -m 128 \
	  -kernel ../kernel/vmlinuz \
	  -initrd initramfs.cpio \
	  -serial mon:stdio \
	  -append "console=ttyS0 quiet acpi=off" \
	  -nographic 
