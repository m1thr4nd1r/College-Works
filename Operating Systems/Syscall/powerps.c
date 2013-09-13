#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/delay.h>

SYSCALL_DEFINE0(powerps)
{
	struct task_struct *task;

	printk("Listando Processos...\n");
	
	for_each_process(task)
		printk("Nome: %s | ID: %d | CPU time: %ldms \n", task->comm, task->pid, task->stime+task->utime);

	return 0;
}