#include <linux/kernel.h>
#include <linux/idr.h>
#include <linux/slab.h>

static struct idr my_idr;

int idr_test(void) {
    int *data = kmalloc(sizeof(int), GFP_KERNEL);
    if (!data) {
        pr_info("Memory allocation failed \n");
        return -1;
    }
    *data = 42;

    idr_init(&my_idr);

    int id = idr_alloc(&my_idr, data, 0, 0, GFP_KERNEL);
    if (id < 0) {
        pr_info("Failed to allocate ID \n");
        kfree(data);
        return -1;
    }
    pr_info("Allocated ID: %d \n", id);

    void *find_data = idr_find(&my_idr, id);
    if (find_data) {
        pr_info("Data found for ID %d: %d \n", id, *(int *)find_data);
    }

    idr_remove(&my_idr, id);
    kfree(find_data);
    kfree(data);

    idr_destroy(&my_idr);
    return 0;
}
