#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/mutex.h>

int process_state_test(void)
{
    pr_info("Testing process state transitions\n");
    pr_info("Current process: PID=%d, Name=%s\n", current->pid, current->comm);

    /* TASK_UNINTERRUPTIBLE 상태 테스트 */
    pr_info("Setting process to TASK_UNINTERRUPTIBLE state\n");
    msleep(20000);
    pr_info("Process woken up from TASK_UNINTERRUPTIBLE state\n");

    return 0;
}
