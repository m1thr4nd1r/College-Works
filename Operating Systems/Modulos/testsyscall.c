#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/unistd.h>

MODULE_LICENSE("Dual BSD/GPL");

void **sys_call_table;

asmlinkage long (*powerps) (void);

/* Init module */

int init_module()
{
	//Baseado no tutorial http://mohsin-junaid.blogspot.com.br/2013/01/android-system-calls-hooking-to-trace.html
    sys_call_table = (void*)0xc0027f84; //ponteiro para a tabela de systemcalls do arquivo System.map. Depois que roda o make no kernel, esse ponteiro pode mudar, vc tem que atualizar
    powerps = sys_call_table[__NR_powerps];

    printk( "chamando....\n");          
    powerps(); // Chama nossa syscall
    printk( "saiu....\n"); 
    
    return 0;
}

/* CLEAN_UP Module */

void cleanup_module()
{
    printk( "Finalizado!!\n");
}