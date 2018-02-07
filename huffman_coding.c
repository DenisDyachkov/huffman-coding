#include "huffman_coding.h"
#include <stdlib.h>

struct encode_buffer* encode_buffer_init() {
    struct encode_buffer *encode_buffer = (struct encode_buffer*)malloc(sizeof(struct encode_buffer));
    if (encode_buffer) {
        encode_buffer->buffer = (unsigned char*)malloc(sizeof(char) * 32);
        if (!encode_buffer->buffer) {
            free(encode_buffer);
            return NULL;
        }
        encode_buffer->capacity = 32;
        encode_buffer->bit_used = 0;
    }
    return encode_buffer;
}

void encode_buffer_free(struct encode_buffer *data) {
    free(data->buffer);
    free(data);
}

struct encode_buffer* encode(struct bit_table *table, const unsigned char *buffer, unsigned size) {
    struct encode_buffer *out = encode_buffer_init();
    for (; size; --size, ++buffer) {
        if (bit_node_empty(table + *buffer)) {
            encode_buffer_free(out);
            return NULL;
        }
        write_bits(&out->buffer, &out->bit_used, &out->capacity, table + *buffer);
    }
    return out;
}

struct encode_buffer* encode_buffer(const unsigned char *buffer, unsigned size) {
    struct priority_queue queue;
    priority_queue_init(&queue);
    bin_to_queue(&queue, buffer, size);
    struct bit_table *table = tree_to_bit_table(&queue);
    struct encode_buffer *result = encode(table, buffer, size);
    //save tree for decode
    return result;
}

unsigned char* decode_buffer(const struct tree_node *root, const unsigned char *buffer, unsigned bit_count) {
    if (root->base.type) return NULL;
    unsigned bit, capacity = 16;
    unsigned char *decode, *head = decode = (unsigned char*)malloc(sizeof(char) * capacity);
    const struct tree_node *node = root;
    for (bit = 0; bit < bit_count; ++bit) {
        if ((buffer[bit >> 3] >> (bit & 7)) & 0x1)  //if ((*buffer >> (bit & 7)) & 0x1)
            node = (struct tree_node*)node->right;
        else
            node = (struct tree_node*)node->left;

        if (node->base.type == NODE_TYPE_LIST) {
            if (head - decode >= capacity) {
                capacity *= 2;
                unsigned char *new = (unsigned char*)realloc(decode, capacity);
                if (!new) {
                    free(decode);
                    return NULL;
                }
                head = new + (head - decode);
                decode = new;
            }

            *head++ = ((struct tree_node_list*)node)->sym;
            node = root;
        }
        //if ((bit & 7) == 7) ++buffer;
    }
    *head = '\0';
    if ((head - decode) + 1 < capacity) { //free up excess memory
        unsigned char *new = (unsigned char*)realloc(decode, (head - decode) + 1);
        if (new)
            decode = new;
    }
    return decode;
}