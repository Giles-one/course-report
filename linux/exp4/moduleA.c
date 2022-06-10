#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

void myPrint(int n, char* msg) {
    printk(KERN_DEBUG "parm is %d %s", n, msg);
} EXPORT_SYMBOL(myPrint);

static int __init cat_module_init(void)	{
	printk(KERN_DEBUG "Hello, module1 's coming \n");
	myPrint(1234, "from modlueA");
    return 0;
}

static void  __exit cat_module_exit(void) {
	printk(KERN_DEBUG "Bye, module1 's leaving \n");
}

module_init(cat_module_init);
module_exit(cat_module_exit);