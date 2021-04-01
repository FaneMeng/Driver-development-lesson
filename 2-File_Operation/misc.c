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
        .name="hello-misc",
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


struct file_operations {
        struct module *owner;
        loff_t (*llseek) (struct file *, loff_t, int);
        ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
        ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
        ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
        ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);
        int (*iterate) (struct file *, struct dir_context *);
        unsigned int (*poll) (struct file *, struct poll_table_struct *);
        long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
        long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
        int (*mmap) (struct file *, struct vm_area_struct *);
        int (*mremap)(struct file *, struct vm_area_struct *);
        int (*open) (struct inode *, struct file *);
        int (*flush) (struct file *, fl_owner_t id);
        int (*release) (struct inode *, struct file *);
        int (*fsync) (struct file *, loff_t, loff_t, int datasync);
        int (*aio_fsync) (struct kiocb *, int datasync);
        int (*fasync) (int, struct file *, int);
        int (*lock) (struct file *, int, struct file_lock *);
        ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);
        unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
        int (*check_flags)(int);
        int (*flock) (struct file *, int, struct file_lock *);
        ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
        ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
        int (*setlease)(struct file *, long, struct file_lock **, void **);
        long (*fallocate)(struct file *file, int mode, loff_t offset,
                          loff_t len);
        void (*show_fdinfo)(struct seq_file *m, struct file *f);
#ifndef CONFIG_MMU
        unsigned (*mmap_capabilities)(struct file *);
#endif
};


extern int misc_register(struct miscdevice *misc);
extern int misc_deregister(struct miscdevice *misc);

module_init(misc_init);
module_exit(misc_exit);
MODULE_LICENSE("GPL");