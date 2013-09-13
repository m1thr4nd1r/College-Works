#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/unistd.h>
#include <linux/sched.h>


MODULE_LICENSE("Dual BSD/GPL");

void **sys_call_table;

/* Init module */

int init_module()
{
    struct task_struct *task;

    printk("Listando Processos...\n");

    for_each_process(task)
        printk("Nome: %s | ID: %d | CPU time: %ldms \n", task->comm, task->pid, task->stime+task->utime);

    return 0;
}

/* CLEAN_UP Module */

void cleanup_module()
{
    printk( "Finalizado!!\n");
}