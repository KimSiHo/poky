#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
    printk("Process Test Module Start");
    printk("Process Test Module Start");

    return 0;
}

void cleanup_module(void)
{
    printk("Process Test Module Remove");
}

MODULE_LICENSE("GPL");
