#include <linux/kernel.h>
#include <linux/kfifo.h>

#define FIFO_SIZE 1024
#define NUM_ELEMENTS 10

struct kfifo fifo;

int queue_test(void) {
    pr_info("fifo create \n");
    if (kfifo_alloc(&fifo, FIFO_SIZE, GFP_KERNEL)) {
        pr_info("error kfifo alloc \n");
        return -ENOMEM;
    }
    pr_info("queue size: %u \n", kfifo_size(&fifo));

    int i;
    for(i=0; i<NUM_ELEMENTS; i++){
        int val=i*10;
        kfifo_in(&fifo, &val, sizeof(val));
    }

    pr_info("queue len: %u \n", kfifo_len(&fifo));
    pr_info("queue available: %u \n", kfifo_avail(&fifo));

    for(i=0; i<NUM_ELEMENTS; i++){
        int val;
        kfifo_out(&fifo, &val, sizeof(val));
        pr_info("%d \n", val);
    }
    pr_info("queue available: %u \n", kfifo_avail(&fifo));

    kfifo_free(&fifo);
    return 0;
}
