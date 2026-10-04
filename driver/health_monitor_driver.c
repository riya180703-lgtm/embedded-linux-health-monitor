#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/miscdevice.h>
#include<linux/uaccess.h>
#include<linux/timekeeping.h>

static ssize_t hm_read(struct file *file, char __user *buf,size_t len, loff_t *off)
{
	char msg[96];
	int n = scnprintf(msg, sizeof(msg),
			"health_monitor: ok, uptime_sec=%lld\n",		 
			(long long)ktime_get_boottime_seconds());
	 return simple_read_from_buffer(buf, len, off, msg, n);
}
static const struct file_operations hm_fops = {
	.owner = THIS_MODULE,
	.read  = hm_read,
};

static struct miscdevice hm_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "health_monitor",
	.fops  = &hm_fops,
	.mode  = 0444,
};

static int __init hm_init(void)
{
	int ret = misc_register(&hm_dev);
	
	if(ret)
	   return ret;
	
	pr_info("health_monitor: /dev/health_monitor created\n");
	return 0;
}

static void __exit hm_exit(void)
{
	misc_deregister(&hm_dev);
	pr_info("health_monitor: kernel module unloaded\n");
}
module_init(hm_init);
module_exit(hm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Riya Kumari");
MODULE_DESCRIPTION("Embedded Linux Health Monitor character device");
MODULE_VERSION("1.0"); 
