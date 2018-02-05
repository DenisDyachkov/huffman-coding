#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include "priority_queue.h"
struct tree_node_base {
    int type;
};

struct tree_node_list {
    struct tree_node_base base;
    unsigned char sym;//uint8_t
};

struct tree_node {
    struct tree_node_base base;
    struct tree_node_base *left;
    struct tree_node_base *right;
};

struct tree_queue_node {
    struct priority_queue_base base;
    struct tree_node_base *tree;
};

void tree_list_create(struct priority_queue *queue, int weight, unsigned char sym);
void queue_to_tree(struct priority_queue *queue);

#endif //HUMAN_HUFFMAN_TREE_HAF