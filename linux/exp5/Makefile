.PHONY: fs run clean
CC = gcc
CFLAGS = -static
CFLAGS += -g

all: exp5.c child.c
	$(CC) child.c $(CFLAGS) -o child && \
	$(CC) exp5.c $(CFLAGS) -o exp
	@cp child exp ./fs
fs:
	@cd fs && find . -print0 | cpio --null -ov --format=newc > ../initramfs.cpio
run:
	@qemu-system-x86_64 \
	  -m 128 \
	  -kernel bzImage \
	  -initrd initramfs.cpio \
	  -serial mon:stdio \
	  -append "console=ttyS0 quiet acpi=off" \
	  -nographic 
clean:
	rm initramfs.cpio child exp
