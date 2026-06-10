#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Derek Molloy");
MODULE_DESCRIPTION("A simple Linux driver.");
MODULE_VERSION("0.1");

static char *name = "world";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name to display in log");

static int __init helloBBB_init(void) {
    printk(KERN_INFO "EBB: Hello %s from the BBB LKM!\n", name);
    return 0;
}

static void __exit helloBBB_exit(void) {
    printk(KERN_INFO "EBB: Goodbye %s from BBB LKM!\n", name);
}

module_init(helloBBB_init);
module_exit(helloBBB_exit);
