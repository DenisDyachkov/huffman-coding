#include "huffman_coding.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern struct tree_node *temp_variable;

int main() {
    const char *src_data = "a person or thing that prevents incompatible or antagonistic people or things from coming into contact with or harming each other.";
    const int length_data = strlen(src_data);//130 byte = 1040 bit
    printf("Source data: '%s'\nBytes: %d  Bits: %d\n", src_data, length_data, length_data << 3);

    struct encode_buffer *compressed = encode_buffer((const unsigned char*)src_data, (unsigned)length_data);
    printf("Compressed data: '%s'\nBits used: %d  Capacity: %d\n", compressed->buffer, compressed->bit_used, compressed->capacity);

    unsigned char *data = decode_buffer(temp_variable, compressed->buffer, compressed->bit_used);
    printf("Decode data: '%s'\nBytes: %d\nThe original and decoded data are the same: %s\n",
           data, strlen((const char*)data), strcmp(src_data, (const char*)data) ? "false" : "true");

    encode_buffer_free(compressed);
    free(data);
    return 0;
}