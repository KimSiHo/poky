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
    struct my_struct *item1, *item2, *item3;

    item1 = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
    if (!item1)
        return -ENOMEM;
    item1->data = 42;
    hlist_add_head(&item1->node, &my_list);

    item2 = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
    if (!item2) {
        kfree(item1);
        return -ENOMEM;
    }
    item2->data = 24;
    hlist_add_head(&item2->node, &my_list);

    item3 = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
    if (!item3) {
        kfree(item1);
        kfree(item2);
        return -ENOMEM;
    }
    item3->data = 84;
    hlist_add_head(&item3->node, &my_list);

    // 리스트 순회
    struct hlist_node *pos;
    pr_info("Traversing the single-linked list\n");
    hlist_for_each(pos, &my_list) {
        struct my_struct *entry = hlist_entry(pos, struct my_struct, node);
        pr_info("Data: %d\n", entry->data);
    }

    // 리스트 정리 및 메모리 해제
    struct hlist_node *pos_safe, *tmp;
    pr_info("Deleting nodes and freeing memory\n");
    hlist_for_each_safe(pos_safe, tmp, &my_list) {
        struct my_struct *entry = hlist_entry(pos_safe, struct my_struct, node);
        pr_info("Freeing node with data: %d\n", entry->data);
        hlist_del(&entry->node);
        kfree(entry);
    }

    return 0;
}
