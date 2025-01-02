#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>

extern int wait_queue_test(void);
extern int gdb_debug_test(void);

char* pttype = "wait-queue";

module_param(pttype, charp, 0644);
MODULE_PARM_DESC(pttype, "process test type: `wait-queue`, `gdb-debug`");

int init_module(void)
{
    pr_info("Process Test Module loaded with process test type=%s \n", pttype);
    if (strcmp(pttype, "wait-queue") == 0) {
        wait_queue_test();
    }

    if (strcmp(pttype, "gdb-debug") == 0) {
        gdb_debug_test();
    }

    return 0;
}

void cleanup_module(void)
{
    pr_info("Process Test Module Remove \n");
}

MODULE_LICENSE("GPL");
