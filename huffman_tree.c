#include "huffman_tree.h"
#include <stdlib.h>

static void tree_list_create(struct priority_queue *queue, int weight, unsigned char sym) {
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

void bin_to_queue(struct priority_queue *queue, const unsigned char *buffer, int size) {
    unsigned char counts[256] = {0};
    int iter;
    for (iter = 0; iter < size; ++iter)
        if (counts[buffer[iter]] < 0xFF)
            ++counts[buffer[iter]];
    for (iter = 0; iter < 256; ++iter)
        if (counts[iter])
            tree_list_create(queue, counts[iter], (unsigned char)iter);
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

static void tree_free(struct tree_node_base *tree) {
    if (tree->type)
        return free(tree);
    tree_free(((struct tree_node*)tree)->left);
    tree_free(((struct tree_node*)tree)->right);
    free(tree);
}

void queue_tree_free(struct priority_queue *queue) {
    struct tree_queue_node *node;
    while ((node = (struct tree_queue_node*)priority_queue_pop(queue)) != NULL) {
        tree_free(node->tree);
        free(node);
    }
}

#ifdef _DEBUG_PRINT_
#include <stdio.h>
void print_tree(struct tree_node_base *tree, char *out_print, int bits) {
    int alloc = 0;
    if (!out_print) {
        out_print = (char*)malloc(24);
        alloc = 1;
    }
    if (tree->type == 1) {
        out_print[bits] = 0;
        printf("'%c': %s\n", ((struct tree_node_list*)tree)->sym, out_print);
        return;
    }

    struct tree_node *node = (struct tree_node*)tree;
    out_print[bits] = '0';
    if (node->left)
        print_tree(node->left, out_print, bits + 1);
    out_print[bits] = '1';
    if (node->right)
        print_tree(node->right, out_print, bits + 1);

    if (alloc)
        free(out_print);
}
#endif