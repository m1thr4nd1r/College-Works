/*
 *    hello.c - Simple example Loadable Kernel Module that prints
 *              output to the syslog
 *
 *    By Mark Loiseau (http://blog.markloiseau.com/2012/04/hello-world-loadable-kernel-module-tutorial/)
 *
 *    Background: http://tldp.org/HOWTO/Module-HOWTO/x73.html
 */

// Defining __KERNEL__ and MODULE allows us to access kernel-level code not usually available to userspace programs.
#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

// Linux Kernel/LKM headers: module.h is needed by all modules and kernel.h is needed for KERN_INFO.
#include <linux/module.h>	// included for all kernel modules
#include <linux/kernel.h>	// included for KERN_INFO
#include <linux/init.h>		// included for __init and __exit macros
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static char *name = "name";

module_param(name, charp, 0000);
MODULE_PARM_DESC(name, "A name");

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello %s!\n", name);
    return 0;	// Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "Goodbye %s!\n", name);
}

module_init(hello_init);
module_exit(hello_cleanup);
