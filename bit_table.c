#include "bit_table.h"
#include <stdlib.h>
#include <mem.h>

#define bits_to_bytes(bits) ((bits + 7) >> 3)
                            //bits >> 3 + (bits & 7 ? 1 : 0);

int write_bits(unsigned char **out, unsigned *used, unsigned *size, struct bit_table *node) {
    if (!out || !*out || !used || !size || !node)
        return 1;

    unsigned need_bits = *used + node->bits_count;
    if (bits_to_bytes(need_bits) > *size) {
        unsigned capacity = (*size * 2 < bits_to_bytes(need_bits)) ? bits_to_bytes(need_bits) : *size * 2;
        unsigned char *new_buffer = (unsigned char*)realloc(*out, capacity);
        if (!new_buffer)
            return -1;
        *size = capacity;
        *out = new_buffer;
    }

    unsigned char *write = *out + (*used >> 3);
    unsigned offset = *used & 7;
    unsigned bit;

    for (bit = 0; bit < node->bits_count; ++bit) {
        if ((node->bits[bit >> 3] >> bit) & 0x1)
            *write |= 1 << offset;
        else
            *write &= ~(1 << offset);
        offset = (offset + 1) & 7;
        if (!offset)
            ++write;
    }
    *used += node->bits_count;
    return 0;
}

static int build_bit_table(struct tree_node_base *tree, struct bit_table *table, unsigned char *bits, unsigned bits_count) {
    if (tree->type == NODE_TYPE_LIST) {
        struct bit_table *node = &table[((struct tree_node_list*)tree)->sym];
        node->bits_count = bits_count;
        unsigned bytes = bits_to_bytes(bits_count);
        node->bits = (unsigned char*)malloc(sizeof(char) * bytes);
        memcpy(node->bits, bits, bytes);
        return 0;
    }

    struct tree_node *node = (struct tree_node*)tree;

    bits[bits_count >> 3] &= ~(0x1 << (bits_count & 7));
    if (node->left && build_bit_table(node->left, table, bits, bits_count + 1))
        return 1;

    bits[bits_count >> 3] |= 0x1 << (bits_count & 7);
    if (node->right && build_bit_table(node->right, table, bits, bits_count + 1))
        return 1;
    return 0;
}

struct bit_table* tree_to_bit_table(struct priority_queue *queue) {
    if (!queue || !queue->size)
        return NULL;
    if (queue->size > 1)
        queue_to_tree(queue);

    struct bit_table *table = (struct bit_table*)calloc(sizeof(struct bit_table), 256);
    unsigned char *bits = (unsigned char*)malloc(sizeof(char) * 2);

    build_bit_table(((struct tree_queue_node*)queue->data)->tree, table, bits, 0);
    free(bits);

    return table;
}

int bit_node_empty(struct bit_table *node) {
    return !node->bits_count;
}