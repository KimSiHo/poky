#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>

struct my_struct {
    int data;
    struct hlist_node node;
};

static struct hlist_head my_list = HLIST_HEAD_INIT;

int single_linked_list_test(void)
{
    struct my_struct *item = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
    if (!item)
        return -ENOMEM;
    item->data = 42;
    hlist_add_head(&item->node, &my_list);

    struct hlist_node *pos;
    hlist_for_each(pos, &my_list) {
        struct my_struct *entry = hlist_entry(pos, struct my_struct, node);
        printk(KERN_INFO "Data: %d", entry->data);
    }

    struct hlist_node *pos_safe, *tmp;
    hlist_for_each_safe(pos_safe, tmp, &my_list) {
        struct my_struct *entry = hlist_entry(pos_safe, struct my_struct, node);
        hlist_del(&entry->node);
        kfree(entry);
    }

    return 0;
}
