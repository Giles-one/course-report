cmd_/home/giles/linux/fly.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/giles/linux/fly.ko /home/giles/linux/fly.o /home/giles/linux/fly.mod.o;  true
