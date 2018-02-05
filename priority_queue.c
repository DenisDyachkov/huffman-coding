#include "priority_queue.h"

void priority_queue_push(struct priority_queue *queue, struct priority_queue_base *new) {
    ++queue->size;
    if (!queue->data || queue->data->weight > new->weight) {
        new->next = queue->data;
        queue->data = new;
        return;
    }

    struct priority_queue_base *node = queue->data;
    while (node->next && node->next->weight < new->weight)
        node = node->next;

    new->next = node->next;
    node->next = new;
}

struct priority_queue_base* priority_queue_pop(struct priority_queue *queue) {
    if (!queue || !queue->size) return 0;
    struct priority_queue_base *node = queue->data;
    queue->data = node->next;
    --queue->size;
    return node;
}

void priority_queue_init(struct priority_queue *queue) {
    queue->size = 0;
    queue->data = 0;
}