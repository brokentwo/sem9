#pragma once
#include <string>
#include <vector>

#include "visual.h"

namespace sem9 {

// Два стека в одном массиве A[1..n] (задание 10.1.2).
// Стек 1 растёт слева направо от A[1], стек 2 — справа налево от A[n].
// top1 = 0 — стек 1 пуст, top2 = n + 1 — стек 2 пуст.
// Массив переполнен только когда top1 + 1 == top2, т.е. всего элементов ровно n.
struct TwoStacks {
    std::vector<Cell> data;  // data[1..n]
    int top1 = 0;
    int top2 = 1;
};

// Создаёт два пустых стека на массиве A[1..n].
// Бросает std::invalid_argument, если n <= 0.
TwoStacks make_two_stacks(int n);

// Количество элементов в стеке 1 и в стеке 2.
int size1(const TwoStacks& s);
int size2(const TwoStacks& s);

// Положить x в стек 1 / стек 2 за O(1).
// Бросают std::overflow_error, если в обоих стеках вместе уже n элементов.
void push1(TwoStacks& s, int x);
void push2(TwoStacks& s, int x);

// Снять верхний элемент стека 1 / стека 2 за O(1).
// Бросают std::underflow_error, если соответствующий стек пуст.
int pop1(TwoStacks& s);
int pop2(TwoStacks& s);

// Печатает общий массив со стрелками top1 и top2.
void print_two_stacks(const TwoStacks& s, const std::string& name);

}  // namespace sem9
