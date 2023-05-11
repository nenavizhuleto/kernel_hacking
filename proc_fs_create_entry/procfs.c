#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

#define M_MAX_USER_SIZE 1024

static char data_buffer[M_MAX_USER_SIZE + 1] = {0};
static struct proc_dir_entry *m_proc = NULL;

ssize_t m_read(struct file *file, char __user *user, size_t size, loff_t *off)
{
    return copy_to_user(user, "Hello!\n", 7) ? 0 : 7;
}

ssize_t m_write(struct file *file, const char __user *user, size_t size, loff_t *off)
{
    memset(data_buffer, 0x0, sizeof(data_buffer));

    if (size > M_MAX_USER_SIZE)
    {
        size = M_MAX_USER_SIZE;
    }

    if (copy_from_user(data_buffer, user, size))
        return 0;

    printk("Data buffer: %s\n", data_buffer);

    return size;
}
static const struct proc_ops m_proc_fops =
    {
        .proc_read = m_read,
        .proc_write = m_write,
};

static int __init m_init(void)
{
    printk(KERN_ALERT "Start of Module #1\n");
    m_proc = proc_create("m_procfs", 0666, NULL, &m_proc_fops);
    return 0;
}
static void __exit m_exit(void)
{
    printk(KERN_ALERT "Exit of Module #1\n");
    proc_remove(m_proc);
    return;
}
module_init(m_init);
module_exit(m_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nenavizhu Leto");
MODULE_DESCRIPTION("Example of procfs entry");
