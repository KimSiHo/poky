#include <linux/kernel.h>
#include <linux/idr.h>
#include <linux/slab.h>

static struct idr my_idr;

int idr_test(void) {
    int *data = kmalloc(sizeof(int), GFP_KERNEL);
    if (!data) {
        printk("Memory allocation failed");
        return -1;
    }
    *data = 42;

    idr_init(&my_idr);

    int id = idr_alloc(&my_idr, data, 0, 0, GFP_KERNEL);
    if (id < 0) {
        printk("Failed to allocate ID");
        kfree(data);
        return -1;
    }
    printk("Allocated ID: %d", id);

    void *find_data = idr_find(&my_idr, id);
    if (find_data) {
        printk("Data found for ID %d: %d", id, *(int *)find_data);
    }

    idr_remove(&my_idr, id);
    kfree(find_data);
    kfree(data);

    idr_destroy(&my_idr);
    printk("버퍼 출력용");
    return 0;
}
