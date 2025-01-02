#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>

extern int wait_queue_test(void);
extern int gdb_debug_test(void);
extern int process_state_test(void);

char* pttype = "process-state";

module_param(pttype, charp, 0644);
MODULE_PARM_DESC(pttype, "process test type: `wait-queue`, `gdb-debug`, `process-state`");

int init_module(void)
{
    pr_info("Process Test Module loaded with process test type=%s \n", pttype);
    if (strcmp(pttype, "wait-queue") == 0) {
        wait_queue_test();
    }

    if (strcmp(pttype, "gdb-debug") == 0) {
        gdb_debug_test();
    }

    if (strcmp(pttype, "process-state") == 0) {
        process_state_test();
    }

    return 0;
}

void cleanup_module(void)
{
    pr_info("Process Test Module Remove \n");
}

MODULE_LICENSE("GPL");
