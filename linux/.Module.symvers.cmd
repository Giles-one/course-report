cmd_/home/giles/linux/Module.symvers := sed 's/ko$$/o/' /home/giles/linux/modules.order | scripts/mod/modpost -m -a   -o /home/giles/linux/Module.symvers -e -i Module.symvers   -T -
