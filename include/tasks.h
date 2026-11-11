#pragma once
#include <string>

namespace sem9 {

// Каждая функция выполняет одно задание семинара и печатает результат.
void run_task_10_1_1();  // стек S[1..6]: PUSH 4, 1, 3, POP, PUSH 8, POP
void run_task_10_1_2();  // два стека в одном массиве A[1..n]
void run_task_10_1_3();  // очередь Q[1..6]: ENQUEUE 4, 1, 3, DEQUEUE, ENQUEUE 8, DEQUEUE
void run_task_10_1_4();  // ENQUEUE / DEQUEUE с проверкой переполнения и опустошения
void run_task_10_1_5();  // дек на массиве: вставка и удаление с обоих концов

// Запускает все пять заданий подряд.
void run_all_tasks();

// Запускает одно задание по номеру ("10.1.1" ... "10.1.5").
// Возвращает false, если такого задания нет.
bool run_task(const std::string& number);

}  // namespace sem9
