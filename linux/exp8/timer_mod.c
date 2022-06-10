#include <linux/init.h>
#include <linux/timer.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

void my_timer_function(struct timer_list* my_timer) {
    printk(KERN_ALERT "after 5 seconds, time come \n");
}

static int func_init(void) {
    static struct timer_list my_timer;
    timer_setup(&my_timer, my_timer_function, 0);
    my_timer.expires = jiffies + 5000;
    my_timer.function = my_timer_function;
    add_timer(&my_timer);
    printk(KERN_ALERT "timer_mod initing..ok \n");
    return 0;
}

static void func_exit(void) {
    printk(KERN_ALERT "timer_mod exiting...ok \n");
}
module_init(func_init);
module_exit(func_exit);