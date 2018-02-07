cmake_minimum_required(VERSION 3.8)
project(huffman)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c priority_queue.c priority_queue.h huffman_tree.c huffman_tree.h bit_table.c bit_table.h huffman_coding.c huffman_coding.h)
add_executable(huffman ${SOURCE_FILES})