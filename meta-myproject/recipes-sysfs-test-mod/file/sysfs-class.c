#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>

static struct class *my_class;
static struct device *my_device;

static ssize_t my_show(struct device *dev, struct device_attribute *attr, char *buf) {
    return sprintf(buf, "Hello, sysfs!\n");
}

static ssize_t my_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
    printk(KERN_INFO "Written to sysfs: %s", buf);
    return count;
}

static DEVICE_ATTR(my_attr, 0664, my_show, my_store);

static int __init my_module_init(void) {
    my_class = class_create(THIS_MODULE, "my_class");
    if (IS_ERR(my_class))
        return PTR_ERR(my_class);

    my_device = device_create(my_class, NULL, MKDEV(240, 0), NULL, "my_device");
    if (IS_ERR(my_device)) {
        class_destroy(my_class);
        return PTR_ERR(my_device);
    }

    if (device_create_file(my_device, &dev_attr_my_attr)) {
        device_destroy(my_class, MKDEV(240, 0));
        class_destroy(my_class);
        return -EIO;
    }

    printk(KERN_INFO "Module loaded: /sys/class/my_class/my_device/my_attr\n");
    return 0;
}

static void __exit my_module_exit(void) {
    device_remove_file(my_device, &dev_attr_my_attr);
    device_destroy(my_class, MKDEV(240, 0));
    class_destroy(my_class);
    printk(KERN_INFO "Module unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
