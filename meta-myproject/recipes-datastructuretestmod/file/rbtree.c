#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/rbtree.h>
#include <linux/slab.h>

struct my_node {
    int key;
    struct rb_node node;
};

static struct rb_root my_tree = RB_ROOT;

void rb_insert(int key) {
    struct rb_node **new = &my_tree.rb_node;
    struct rb_node *parent = NULL;
    struct my_node *new_node;

    while (*new) {
        struct my_node *this = container_of(*new, struct my_node, node);
        parent = *new;

        if (key < this->key)
            new = &(*new)->rb_left;
        else if (key > this->key)
            new = &(*new)->rb_right;
        else
            return;
    }

    new_node = kmalloc(sizeof(struct my_node), GFP_KERNEL);
    if (!new_node)
        return;

    new_node->key = key;
    rb_link_node(&new_node->node, parent, new);
    rb_insert_color(&new_node->node, &my_tree);
}

struct my_node *rb_search(int key) {
    struct rb_node *node = my_tree.rb_node;

    while (node) {
        struct my_node *data = container_of(node, struct my_node, node);

        if (key < data->key)
            node = node->rb_left;
        else if (key > data->key)
            node = node->rb_right;
        else
            return data; // 찾은 경우
    }
    return NULL; // 키를 찾지 못한 경우
}

int rbtree_test(void) {
    rb_insert(10);
    rb_insert(20);
    rb_insert(30);
    rb_insert(25);

    struct my_node *found_node = rb_search(25);
    if (found_node)
        pr_info("Found key %d \n", found_node->key);
    else
        pr_info("Key not found \n");

    return 0;
}
