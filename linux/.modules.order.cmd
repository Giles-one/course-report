cmd_/home/giles/linux/modules.order := {   echo /home/giles/linux/fly.ko; :; } | awk '!x[$$0]++' - > /home/giles/linux/modules.order
