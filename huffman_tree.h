#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include "priority_queue.h"
#define NODE_TYPE_LIST 1
#define NODE_TYPE_NODE 0

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

void bin_to_queue(struct priority_queue *queue, const char *buffer, int size);
void queue_to_tree(struct priority_queue *queue);
void queue_tree_free(struct priority_queue *queue);

#ifdef _DEBUG_PRINT_
void print_tree(struct tree_node_base *tree, char *out_print, int bits);
#endif //_DEBUG_PRINT_

#endif //HUFFMAN_HUFFMAN_TREE_HAF