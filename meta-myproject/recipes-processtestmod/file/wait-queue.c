#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static int test_thread_fn(void *data);
void start_test_thread(void);

static DECLARE_WAIT_QUEUE_HEAD(my_queue);
static int condition = 0;
static struct task_struct *test_thread;

int wait_queue_test(void)
{
    pr_info("wait_queue_test. Current process: %s (pid: %d)\n", current->comm, current->pid);
    start_test_thread();

    pr_info("Process %s added to wait queue.\n", current->comm);
    int ret = wait_event_interruptible(my_queue, condition != 0);
    if (ret == -ERESTARTSYS) {
        pr_info("Interrupted by signal.\n");
    }

    pr_info("Process %s removed from wait queue.\n", current->comm);
    return 0;
}

void start_test_thread(void)
{
    test_thread = kthread_run(test_thread_fn, NULL, "test_thread");
    if (IS_ERR(test_thread)) {
        pr_err("Failed to create test thread.\n");
        return;
    }
    pr_info("Test thread created successfully.\n");
}

static int test_thread_fn(void *data)
{
    pr_info("Test thread started. Current process: %s (pid: %d)\n", current->comm, current->pid);

    ssleep(30);
    condition = 1;
    pr_info("Condition met, waking up processes in wait queue.\n");
    wake_up_interruptible(&my_queue);

    return 0;
}
