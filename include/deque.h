#pragma once
#include <string>
#include <vector>

#include "visual.h"

namespace sem9 {

// Дек (очередь с двусторонним доступом) на кольцевом массиве D[1..n] (задание 10.1.5).
// head — номер первого элемента, tail — ячейка сразу после последнего.
// head == tail — дек пуст; помещается не больше n - 1 элементов.
struct Deque {
    std::vector<Cell> data;  // data[1..n]
    int head = 1;
    int tail = 1;
    int length = 0;
};

// Создаёт пустой дек на массиве D[1..n].
// Бросает std::invalid_argument, если n < 2.
Deque make_deque(int n);

bool deque_empty(const Deque& d);
bool deque_full(const Deque& d);

// Все четыре операции выполняются за O(1).
// Вставки бросают std::overflow_error, удаления — std::underflow_error.
void push_front(Deque& d, int x);  // вставка в голову
void push_back(Deque& d, int x);   // вставка в хвост
int pop_front(Deque& d);           // удаление из головы
int pop_back(Deque& d);            // удаление из хвоста

// Печатает массив дека со стрелками head и tail.
void print_deque(const Deque& d, const std::string& name);

}  // namespace sem9
