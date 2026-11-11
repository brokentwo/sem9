#include "queue.h"

#include <stdexcept>

namespace sem9 {

namespace {

constexpr int kMinQueueLength = 2;

// Следующий номер ячейки по кругу: после n идёт 1.
int next_index(const Queue& q, int i) {
    return i == q.length ? 1 : i + 1;
}

}  // namespace

Queue make_queue(int n) {
    if (n < kMinQueueLength) {
        throw std::invalid_argument("длина очереди должна быть не меньше 2");
    }
    Queue q;
    q.data.assign(static_cast<std::size_t>(n) + 1, std::nullopt);
    q.length = n;
    q.head = 1;
    q.tail = 1;
    return q;
}

void enqueue_unchecked(Queue& q, int x) {
    q.data[q.tail] = x;
    if (q.tail == q.length) {
        q.tail = 1;
    } else {
        q.tail = q.tail + 1;
    }
}

int dequeue_unchecked(Queue& q) {
    const int x = q.data[q.head].value_or(0);
    if (q.head == q.length) {
        q.head = 1;
    } else {
        q.head = q.head + 1;
    }
    return x;
}

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

void print_queue(const Queue& q, const std::string& name) {
    std::vector<bool> active(q.data.size(), false);
    for (int i = q.head; i != q.tail; i = next_index(q, i)) {
        active[i] = true;
    }
    print_array(name, q.data, active, {{name + ".head", q.head}, {name + ".tail", q.tail}});
}

}  // namespace sem9
