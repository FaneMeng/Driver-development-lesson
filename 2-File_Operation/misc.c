/***
 * 
 File operation development exercise
 by Fane Meng 2021.04
 ***/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

ssize_t misc_read (struct file *file, char __user *ubuf, size_t size, loff_t *loff_t)
{
    printk("MISC devive read\n");
    return 0;
}

ssize_t misc_write (struct file *file, char __user *ubuf, size_t size, loff_t *loff_t)
{
    printk("MISC devive write\n");
    return 0;
}

int misc_open (struct inode *inode, struct file *file)
{
    printk("MISC device open\n");
    return 0;
}


int misc_release (struct inode *inode, struct file *file)
{
    printk("MISC device release\n");
    return 0;
}


struct file_operations misc__fops = {                          
        .owner   = THIS_MODULE,
        .read    = misc_read,
        .write   = misc_write,
        .open    = misc_open,
        .release = misc_release
};

struct miscdevice misc_dev = {
        .minor=MISC_DYNAMIC_MINOR,
        .name="hello_misc",
        .fops = &misc__fops

};

static int misc_init(void){
    int ret = misc_register(&misc_dev);
    if(ret<0)
    {
        printk("MISC device init failed!\n");
        return -1;
    }
    printk("MISC device is installed\n");
    return 0;
}

static void misc_exit(void)
{
    misc_deregister(&misc_dev);
    printk("MISC device is removed\n");
}

extern int misc_register(struct miscdevice *misc);
extern int misc_deregister(struct miscdevice *misc);

module_init(misc_init);
module_exit(misc_exit);
MODULE_LICENSE("GPL");