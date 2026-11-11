#pragma once
#include <string>
#include <vector>

#include "visual.h"

namespace sem9 {

// Кольцевая очередь на массиве Q[1..n] (рис. 10.2).
// head — номер первого элемента, tail — номер ячейки, куда встанет следующий.
// head == tail — очередь пуста. Одна ячейка всегда свободна, поэтому
// в очереди помещается не больше n - 1 элементов.
struct Queue {
    std::vector<Cell> data;  // data[1..n]
    int head = 1;
    int tail = 1;
    int length = 0;  // Q.length = n
};

// Создаёт пустую очередь на массиве Q[1..n] (head = tail = 1).
// Бросает std::invalid_argument, если n < 2 (иначе в очередь не влезет ни один элемент).
Queue make_queue(int n);

// ENQUEUE и DEQUEUE точно как в учебнике — без проверок (используются в 10.1.3).
// На пустой или полной очереди портят её состояние.
void enqueue_unchecked(Queue& q, int x);
int dequeue_unchecked(Queue& q);

// Очередь пуста: head == tail.
bool queue_empty(const Queue& q);

// Очередь полна: следующая ячейка после tail — это head.
bool queue_full(const Queue& q);

// Количество элементов в очереди.
int queue_size(const Queue& q);

// ENQUEUE с проверкой (задание 10.1.4).
// Бросает std::overflow_error ("overflow"), если очередь полна.
void enqueue(Queue& q, int x);

// DEQUEUE с проверкой (задание 10.1.4).
// Бросает std::underflow_error ("underflow"), если очередь пуста.
int dequeue(Queue& q);

// Печатает массив очереди со стрелками head и tail.
void print_queue(const Queue& q, const std::string& name);

}  // namespace sem9
