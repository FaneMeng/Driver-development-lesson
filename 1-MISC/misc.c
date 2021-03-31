/***
 * 
 misc device driver development exercise
 by Fane Meng 2021.03
 ***/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

struct file_operations misc__fops = {                          
        .owner   = THIS_MODULE
};

struct miscdevice misc_dev = {
        .minor=MISC_DYNAMIC_MINOR,
        .name="hello-misc",
        .file_operations = &misc__fops

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