#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
// https://github.com/xcellerator/linux_kernel_hacking/issues/3

static struct kprobe kp = {
    .symbol_name = "get_private_password"};

typedef unsigned long (*get_private_password_t)(void);

static int __init hack_init(void)
{
    printk(KERN_INFO "hack modular installed successfully\n");
    get_private_password_t get_private_password;
    register_kprobe(&kp);
    printk(KERN_ALERT "get_private_password() address: 0x%px \n", kp.addr - 0x4);
    get_private_password = (get_private_password_t)(kp.addr - 0x4);
    unregister_kprobe(&kp);
    char *private_password = (char *)get_private_password();
    printk(KERN_ALERT "password is %s\n", private_password);
    return 0;
}

static void __exit hack_exit(void)
{
    printk(KERN_INFO "hack modular removed successfully\n");
    return;
}

module_init(hack_init);
module_exit(hack_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HACKER GUY");