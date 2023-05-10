#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

static char *private_password = "super_secret_string";

char *get_private_password(void)
{
    return private_password;
}

EXPORT_SYMBOL(get_private_password);

static int __init secure_init(void)
{

    printk(KERN_INFO "secure modular installed successfully\n");
    return 0;
}

static void __exit secure_exit(void)
{
    printk(KERN_INFO "secure modular removed successfully\n");
    return;
}

module_init(secure_init);
module_exit(secure_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SECURITY GUY");