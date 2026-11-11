#include "stack.h"

#include <stdexcept>

namespace sem9 {

Stack make_stack(int n) {
    if (n <= 0) {
        throw std::invalid_argument("размер стека должен быть положительным");
    }
    Stack s;
    s.data.assign(static_cast<std::size_t>(n) + 1, std::nullopt);
    s.top = 0;
    return s;
}

bool stack_empty(const Stack& s) {
    return s.top == 0;
}

void push(Stack& s, int x) {
    const int n = static_cast<int>(s.data.size()) - 1;
    if (s.top == n) {
        throw std::overflow_error("overflow");
    }
    s.top = s.top + 1;
    s.data[s.top] = x;
}

int pop(Stack& s) {
    if (stack_empty(s)) {
        throw std::underflow_error("underflow");
    }
    s.top = s.top - 1;
    return *s.data[s.top + 1];
}

void print_stack(const Stack& s, const std::string& name) {
    std::vector<bool> active(s.data.size(), false);
    for (int i = 1; i <= s.top; ++i) {
        active[i] = true;
    }
    print_array(name, s.data, active, {{name + ".top", s.top}});
}

}  // namespace sem9
