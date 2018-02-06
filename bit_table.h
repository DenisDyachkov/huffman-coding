#ifndef HUFFMAN_BIT_TABLE_H
#define HUFFMAN_BIT_TABLE_H

#include "huffman_tree.h"

struct bit_table {
    int bits_count;
    unsigned char *bits;
};

struct bit_table* tree_to_bit_table(struct priority_queue *queue);//return bit_table[256]
int write_bits(unsigned char **out_buffer, unsigned *bits_used, unsigned *buffer_size_bytes, struct bit_table *node);

#endif //HUFFMAN_BIT_TABLE_H