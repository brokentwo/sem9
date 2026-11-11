#pragma once
#include "task_10_1_3_queue.h"

namespace sem9 {

// Задание 10.1.4. ENQUEUE и DEQUEUE, которые обнаруживают опустошение и переполнение
// очереди из задания 10.1.3.

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

}  // namespace sem9
