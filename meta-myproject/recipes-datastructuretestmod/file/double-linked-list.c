#include <linux/kernel.h>
#include <linux/list.h>

typedef struct node {
    int data;
    struct list_head list;
}Node;

int double_linked_list_test(void)
{
    LIST_HEAD(node_list);
    printk("Address of node_list: %p\n", &node_list);
    Node node1;
    Node node2;
    Node node3;
    Node node4;
    Node *now;

    printk("List Insert");
    node1.data=111;
    node2.data=222;
    node3.data=333;
    node4.data=444;

    list_add(&node1.list, &node_list);
    list_add(&node2.list, &node_list);
    list_add(&node3.list, &node_list);

    list_for_each_entry(now, &node_list, list) {
        printk("insert data => %d, list_head(now) => %p, list_head(next) => %p, list_head(prev) => %p\n",
                now->data, &now->list, now->list.next, now->list.prev);
    }

    printk("List Delete");
    list_del(&node2.list);

    list_for_each_entry(now, &node_list, list) {
        printk("delete data => %d, list_head(now) => %p, list_head(next) => %p, list_head(prev) => %p\n",
                now->data, &now->list, now->list.next, now->list.prev);
    }

    printk("List Replace");
    list_replace(&node3.list, &node4.list);

    list_for_each_entry(now, &node_list, list) {
        printk("replace data => %d, list_head(now) => %p, list_head(next) => %p, list_head(prev) => %p\n",
                now->data, &now->list, now->list.next, now->list.prev);
    }

    return 0;
}
