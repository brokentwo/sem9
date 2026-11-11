#include "deque.h"

#include <stdexcept>

namespace sem9 {

namespace {

constexpr int kMinDequeLength = 2;

// Соседние ячейки по кругу: после n идёт 1, перед 1 стоит n.
int next_index(const Deque& d, int i) {
    return i == d.length ? 1 : i + 1;
}

int prev_index(const Deque& d, int i) {
    return i == 1 ? d.length : i - 1;
}

}  // namespace

Deque make_deque(int n) {
    if (n < kMinDequeLength) {
        throw std::invalid_argument("длина дека должна быть не меньше 2");
    }
    Deque d;
    d.data.assign(static_cast<std::size_t>(n) + 1, std::nullopt);
    d.length = n;
    d.head = 1;
    d.tail = 1;
    return d;
}

bool deque_empty(const Deque& d) {
    return d.head == d.tail;
}

bool deque_full(const Deque& d) {
    return next_index(d, d.tail) == d.head;
}

void push_front(Deque& d, int x) {
    if (deque_full(d)) {
        throw std::overflow_error("overflow");
    }
    d.head = prev_index(d, d.head);  // голова сдвигается влево
    d.data[d.head] = x;
}

void push_back(Deque& d, int x) {
    if (deque_full(d)) {
        throw std::overflow_error("overflow");
    }
    d.data[d.tail] = x;
    d.tail = next_index(d, d.tail);  // хвост сдвигается вправо
}

int pop_front(Deque& d) {
    if (deque_empty(d)) {
        throw std::underflow_error("underflow");
    }
    const int x = *d.data[d.head];
    d.head = next_index(d, d.head);
    return x;
}

int pop_back(Deque& d) {
    if (deque_empty(d)) {
        throw std::underflow_error("underflow");
    }
    d.tail = prev_index(d, d.tail);  // последний элемент стоит перед tail
    return *d.data[d.tail];
}

void print_deque(const Deque& d, const std::string& name) {
    std::vector<bool> active(d.data.size(), false);
    for (int i = d.head; i != d.tail; i = next_index(d, i)) {
        active[i] = true;
    }
    print_array(name, d.data, active, {{name + ".head", d.head}, {name + ".tail", d.tail}});
}

}  // namespace sem9
