#include <linux/kernel.h>
#include <linux/kfifo.h>

#define FIFO_SIZE 1024
#define NUM_ELEMENTS 10

struct kfifo fifo;

int queue_test(void) {
    printk("fifo create");
    if (kfifo_alloc(&fifo, FIFO_SIZE, GFP_KERNEL)) {
        printk("error kfifo alloc");
        return -ENOMEM;
    }
    printk("queue size: %u", kfifo_size(&fifo));

    int i;
    for(i=0; i<NUM_ELEMENTS; i++){
        int val=i*10;
        kfifo_in(&fifo, &val, sizeof(val));
    }

    printk(KERN_INFO "queue len: %u", kfifo_len(&fifo));
    printk(KERN_WARNING "queue available: %u", kfifo_avail(&fifo));

    for(i=0; i<NUM_ELEMENTS; i++){
        int val;
        kfifo_out(&fifo, &val, sizeof(val));
        printk("%d", val);
    }
    printk("queue available: %u", kfifo_avail(&fifo));

    kfifo_free(&fifo);
    printk("fifo free");
    return 0;
}
