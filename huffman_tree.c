#include "huffman_tree.h"
#include <stdlib.h>

#define NODE_TYPE_LIST 1
#define NODE_TYPE_NODE 0

void tree_list_create(struct priority_queue *queue, int weight, unsigned char sym) {
    if (queue) {
        struct tree_queue_node *node = (struct tree_queue_node*)malloc(sizeof(struct tree_queue_node));
        struct tree_node_list *list = (struct tree_node_list*)malloc(sizeof(struct tree_node_list));

        list->sym = sym;
        list->base.type = NODE_TYPE_LIST;

        node->tree = (struct tree_node_base*)list;
        node->base.weight = weight;

        priority_queue_push(queue, (struct priority_queue_base*)node);
    }
}

void queue_to_tree(struct priority_queue *queue) {
    if (!queue) return;
    while (queue->size > 1) {
        struct tree_queue_node *left = (struct tree_queue_node*)priority_queue_pop(queue);
        struct tree_queue_node *right = (struct tree_queue_node*)priority_queue_pop(queue);
        struct tree_node *node = (struct tree_node*)malloc(sizeof(struct tree_node));
        node->base.type = NODE_TYPE_NODE;
        node->left = left->tree;
        node->right = right->tree;

        left->base.weight += right->base.weight;

        free(right);

        left->tree = (struct tree_node_base*)node;

        priority_queue_push(queue, (struct priority_queue_base*)left);
    }
}