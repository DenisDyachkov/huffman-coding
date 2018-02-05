#ifndef HUFFMAN_PRIORITY_QUEUE_H
#define HUFFMAN_PRIORITY_QUEUE_H

struct priority_queue_base {
    struct priority_queue_base *next;
    int weight;
    //data...
};

struct priority_queue {
    struct priority_queue_base *data;
    int size;
};

void priority_queue_init(struct priority_queue *queue);
void priority_queue_push(struct priority_queue *queue, struct priority_queue_base *new);
struct priority_queue_base* priority_queue_pop(struct priority_queue *queue);

#endif //HUFFMAN_PRIORITY_QUEUE_H
