#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>

extern int double_linked_list_test(void);
extern int single_linked_list_test(void);
extern int queue_test(void);
extern int idr_test(void);
extern int rbtree_test(void);

char* dstype = "sllist";

module_param(dstype, charp, 0644);
MODULE_PARM_DESC(dstype, "data structure type: `dllist`, `sllist`, `queue`, `idr`, 'rbtree'");

int init_module(void)
{
    pr_info("Module loaded with dstype=%s \n", dstype);
    if (strcmp(dstype, "dllist") == 0) {
        double_linked_list_test();
    }

    if (strcmp(dstype, "sllist") == 0) {
        single_linked_list_test();
    }

    if (strcmp(dstype, "queue") == 0) {
        queue_test();
    }

    if (strcmp(dstype, "idr") == 0) {
        idr_test();
    }

    if (strcmp(dstype, "rbtree") == 0) {
        rbtree_test();
    }

    return 0;
}

void cleanup_module(void)
{
    pr_info("Data Structure Module Remove \n");
}

MODULE_LICENSE("GPL");
