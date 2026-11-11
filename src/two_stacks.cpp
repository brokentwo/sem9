#include "two_stacks.h"

#include <stdexcept>

namespace sem9 {

namespace {

int capacity(const TwoStacks& s) {
    return static_cast<int>(s.data.size()) - 1;
}

bool is_full(const TwoStacks& s) {
    return s.top1 + 1 == s.top2;  // между вершинами не осталось свободных ячеек
}

}  // namespace

TwoStacks make_two_stacks(int n) {
    if (n <= 0) {
        throw std::invalid_argument("размер массива должен быть положительным");
    }
    TwoStacks s;
    s.data.assign(static_cast<std::size_t>(n) + 1, std::nullopt);
    s.top1 = 0;
    s.top2 = n + 1;
    return s;
}

int size1(const TwoStacks& s) {
    return s.top1;
}

int size2(const TwoStacks& s) {
    return capacity(s) + 1 - s.top2;
}

void push1(TwoStacks& s, int x) {
    if (is_full(s)) {
        throw std::overflow_error("overflow");
    }
    s.top1 = s.top1 + 1;
    s.data[s.top1] = x;
}

void push2(TwoStacks& s, int x) {
    if (is_full(s)) {
        throw std::overflow_error("overflow");
    }
    s.top2 = s.top2 - 1;
    s.data[s.top2] = x;
}

int pop1(TwoStacks& s) {
    if (s.top1 == 0) {
        throw std::underflow_error("underflow");
    }
    s.top1 = s.top1 - 1;
    return *s.data[s.top1 + 1];
}

int pop2(TwoStacks& s) {
    if (s.top2 == capacity(s) + 1) {
        throw std::underflow_error("underflow");
    }
    s.top2 = s.top2 + 1;
    return *s.data[s.top2 - 1];
}

void print_two_stacks(const TwoStacks& s, const std::string& name) {
    std::vector<bool> active(s.data.size(), false);
    for (int i = 1; i <= s.top1; ++i) {
        active[i] = true;
    }
    for (int i = s.top2; i <= capacity(s); ++i) {
        active[i] = true;
    }
    print_array(name, s.data, active, {{"top1", s.top1}, {"top2", s.top2}});
}

}  // namespace sem9
