#pragma once
#include <string>
#include <vector>

#include "visual.h"

namespace sem9 {

// Стек на массиве S[1..n] (рис. 10.1). top — номер верхнего элемента, 0 — стек пуст.
struct Stack {
    std::vector<Cell> data;  // data[1..n], data[0] не используется
    int top = 0;
};

// Создаёт пустой стек на массиве S[1..n].
// Бросает std::invalid_argument, если n <= 0.
Stack make_stack(int n);

// STACK-EMPTY(S): true, если в стеке нет элементов.
bool stack_empty(const Stack& s);

// PUSH(S, x): кладёт x на вершину стека.
// Бросает std::overflow_error, если массив уже заполнен.
void push(Stack& s, int x);

// POP(S): снимает и возвращает верхний элемент.
// Бросает std::underflow_error ("underflow"), если стек пуст.
int pop(Stack& s);

// Печатает массив стека в стиле рис. 10.1 со стрелкой S.top.
void print_stack(const Stack& s, const std::string& name);

}  // namespace sem9
