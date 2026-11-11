#include "task_10_1_4_queue_checked.h"

#include <stdexcept>

namespace sem9 {

bool queue_empty(const Queue& q) {
    return q.head == q.tail;
}

bool queue_full(const Queue& q) {
    return next_index(q, q.tail) == q.head;
}

int queue_size(const Queue& q) {
    return (q.tail - q.head + q.length) % q.length;
}

void enqueue(Queue& q, int x) {
    if (queue_full(q)) {
        throw std::overflow_error("overflow");
    }
    enqueue_unchecked(q, x);
}

int dequeue(Queue& q) {
    if (queue_empty(q)) {
        throw std::underflow_error("underflow");
    }
    return dequeue_unchecked(q);
}

}  // namespace sem9
