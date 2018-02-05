cmake_minimum_required(VERSION 3.8)
project(haffman)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c priority_queue.c priority_queue.h)
add_executable(haffman ${SOURCE_FILES})