#include "huffman_coding.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char* generateString(unsigned size) {
    char *str = (char*)malloc(size + 1);
    unsigned i;
    srand(time(0));
    for (i = 0; i < size; ++i)
        if ((rand() % 11) & 4)
            str[i] = (char)(rand() % ('Z' - 'A') + 'A');
        else
            str[i] = (char)(rand() % ('z' - 'a') + 'a');
    str[i] = 0;
    return str;
}

extern struct tree_node *temp_variable;

int main() {
    const char *src_data = generateString(1024 * 1024 * 64);
    const unsigned length_data = strlen(src_data);
    printf("Source data (first 32 characters): '%.32s'\nBytes: %u  Bits: %u\n", src_data, length_data, length_data << 3);

    struct encode_buffer *compressed = encode_buffer((const unsigned char*)src_data, length_data);
    printf("\nBits used: %u  Capacity: %d\nCompressed percent: %.2f%%\n\n", compressed->bit_used, compressed->capacity, (1.f - (float)compressed->bit_used / (float)(length_data << 3)) * 100.f);

    unsigned char *data = decode_buffer(temp_variable, compressed->buffer, compressed->bit_used);
    printf("Decode data (first 32 characters): '%.32s'\nBytes: %d\n\nThe original and decoded data are the same: \"%s\"\n",
           data, strlen((const char*)data), strncmp(src_data, (const char*)data, length_data) ? "false" : "true");

    encode_buffer_free(compressed);
    free(data);
    return 0;
}