1. Download Kernel

	wget "https://mirrors.cloud.tencent.com/linux-kernel/v5.x/linux-5.15.tar.xz"
	tar -xf ./linux-5.15.tar.xz 
	cd linux-5.15

2. Add new syscall

	patch -p1 < ../test5.patch 
	-----or------
	vim arch/x86/entry/syscalls/syscall_64.tbl
	vim include/linux/syscalls.h
	vim kernel/sys.c

3. Install toolchain to build kernel

	sudo apt-get install make gcc bison flex libssl-dev ncurses-dev bc libdw-dev zstd

4. Prepare .config file

	make menuconfig      // turn off [compile the kernel with debug info]
	sed -i -e 's/debian\/canonical-certs.pem//' -e 's/debian\/canonical-revoked-certs.pem//' .config

5. Make & make install
	
	make -j$(nproc)      // 生死由命，富贵在天
	sudo make modules_install
	sudo make install




