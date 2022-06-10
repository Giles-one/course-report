#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");

static struct workqueue_struct * queue = NULL;
static struct delayed_work dwork;

void work_handle(struct work_struct * work) {
    printk(KERN_ALERT "after 5 seconds, work running....\n"); 
}

static int init_workqueue(void)
{
    queue = create_workqueue("queue_events");
    printk(KERN_ALERT "workqueue.mod loading....ok\n");
    
    if(queue == NULL) {
        printk(KERN_ALERT "create workqueue error\n");
        return -1;
    }
    
    INIT_DELAYED_WORK(&dwork, work_handle);
    printk(KERN_ALERT "work_handle init....ok\n");
    queue_delayed_work(queue, &dwork, 3000);
    return 0;
}

static void exit_workqueue(void)
{
    flush_workqueue(queue);
    cancel_delayed_work(&dwork);
    destroy_workqueue(queue);
    printk(KERN_ALERT "workqueue unloading....ok\n");
}
module_init(init_workqueue);
module_exit(exit_workqueue);