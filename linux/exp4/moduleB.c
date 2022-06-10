#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cat03");

extern void myPrint(int n, char* msg);

static int __init cat_module_init(void)
{
	printk(KERN_DEBUG "Hello, module2 's coming \n");
	myPrint(5678, "from moduleB");
    return 0;
}
static void  __exit cat_module_exit(void)
{
	printk(KERN_DEBUG "Bye, module2 's leaving \n");
}


module_init(cat_module_init);
module_exit(cat_module_exit);