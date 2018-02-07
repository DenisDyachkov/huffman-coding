#ifndef HUFFMAN_HUFFMAN_CODING_H
#define HUFFMAN_HUFFMAN_CODING_H

#include "bit_table.h"

struct encode_buffer {
    unsigned char *buffer;
    unsigned bit_used;
    unsigned capacity;
};

void encode_buffer_free(struct encode_buffer *data);

struct encode_buffer* encode_buffer(const unsigned char *buffer, unsigned size);
unsigned char* decode_buffer(const struct tree_node *root, const unsigned char *buffer, unsigned bit_count);

#endif //HUFFMAN_HUFFMAN_CODING_H
