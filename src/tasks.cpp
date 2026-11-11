#include "tasks.h"

#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <utility>

#include "task_10_1_1_stack.h"
#include "task_10_1_2_two_stacks.h"
#include "task_10_1_4_queue_checked.h"
#include "task_10_1_5_deque.h"
#include "visual.h"

namespace sem9 {

namespace {

constexpr int kArraySize = 6;       // S[1..6], Q[1..6], A[1..6], D[1..6] из условий
constexpr int kSmallQueueSize = 4;  // Q[1..4] для демонстрации переполнения

void print_title(const std::string& title) {
    std::cout << "==================== " << title << " ====================\n\n";
}

void print_step(const std::string& text) {
    std::cout << ">> " << text << '\n';
}

// Выполняет операцию, которая может бросить исключение, и печатает ошибку.
void try_step(const std::string& text, const std::function<void()>& action) {
    print_step(text);
    try {
        action();
    } catch (const std::exception& e) {
        std::cout << "   ошибка: " << e.what() << '\n';
    }
}

}  // namespace

void run_task_10_1_1() {
    print_title("Задание 10.1.1. Стек S[1..6]");
    print_legend();
    Stack s = make_stack(kArraySize);
    print_step("Пустой стек");
    print_stack(s, "S");

    for (int x : {4, 1, 3}) {
        push(s, x);
        print_step("PUSH(S, " + std::to_string(x) + ")");
        print_stack(s, "S");
    }
    int value = pop(s);
    print_step("POP(S) вернула " + std::to_string(value));
    print_stack(s, "S");

    push(s, 8);
    print_step("PUSH(S, 8)  — 8 записывается поверх старой 3");
    print_stack(s, "S");

    value = pop(s);
    print_step("POP(S) вернула " + std::to_string(value));
    print_stack(s, "S");
    std::cout << "Итог: в стеке 4, 1 (вершина — 1), S.top = 2; число 8 осталось в S[3],"
                 " но стеку не принадлежит.\n\n";
}

void run_task_10_1_2() {
    print_title("Задание 10.1.2. Два стека в одном массиве A[1..6]");
    std::cout << "Стек 1 растёт от A[1] вправо, стек 2 — от A[n] влево.\n"
                 "Переполнение только при top1 + 1 == top2, т.е. когда в двух стеках вместе n "
                 "элементов.\nКаждая операция меняет один индекс и одну ячейку — O(1).\n\n";
    TwoStacks s = make_two_stacks(kArraySize);
    print_step("Пустые стеки: top1 = 0, top2 = n + 1 = 7");
    print_two_stacks(s, "A");

    push1(s, 1);
    push1(s, 2);
    print_step("PUSH1(1), PUSH1(2)");
    print_two_stacks(s, "A");

    push2(s, 9);
    push2(s, 8);
    push2(s, 7);
    print_step("PUSH2(9), PUSH2(8), PUSH2(7)");
    print_two_stacks(s, "A");

    push1(s, 3);
    print_step("PUSH1(3) — массив заполнен: 3 + 3 = 6 = n");
    print_two_stacks(s, "A");

    try_step("PUSH1(4)", [&s] { push1(s, 4); });
    const int value = pop2(s);
    print_step("POP2() вернула " + std::to_string(value) + " — освободилась ячейка A[4]");
    push1(s, 4);
    print_step("PUSH1(4) — теперь стек 1 занимает 4 ячейки, стек 2 — 2");
    print_two_stacks(s, "A");
    std::cout << "Размеры: стек 1 = " << size1(s) << ", стек 2 = " << size2(s) << "\n\n";
}

void run_task_10_1_3() {
    print_title("Задание 10.1.3. Очередь Q[1..6]");
    print_legend();
    Queue q = make_queue(kArraySize);
    print_step("Пустая очередь: Q.head = Q.tail = 1");
    print_queue(q, "Q");

    for (int x : {4, 1, 3}) {
        enqueue_unchecked(q, x);
        print_step("ENQUEUE(Q, " + std::to_string(x) + ")");
        print_queue(q, "Q");
    }
    int value = dequeue_unchecked(q);
    print_step("DEQUEUE(Q) вернула " + std::to_string(value));
    print_queue(q, "Q");

    enqueue_unchecked(q, 8);
    print_step("ENQUEUE(Q, 8)");
    print_queue(q, "Q");

    value = dequeue_unchecked(q);
    print_step("DEQUEUE(Q) вернула " + std::to_string(value));
    print_queue(q, "Q");
    std::cout << "Итог: в очереди 3, 8 (голова — 3), Q.head = 3, Q.tail = 5.\n\n";
}

void run_task_10_1_4() {
    print_title("Задание 10.1.4. ENQUEUE и DEQUEUE с проверками, Q[1..4]");
    std::cout << "Пуста:  Q.head == Q.tail.\n"
                 "Полна:  Q.head == Q.tail + 1, или Q.head == 1 и Q.tail == Q.length.\n"
                 "Одна ячейка всегда свободна, иначе полную очередь нельзя отличить от пустой.\n\n";
    Queue q = make_queue(kSmallQueueSize);
    print_queue(q, "Q");
    try_step("DEQUEUE(Q) на пустой очереди", [&q] { dequeue(q); });

    for (int x : {10, 20, 30}) {
        enqueue(q, x);
    }
    print_step("ENQUEUE 10, 20, 30 — очередь полна (3 = n - 1 элемента)");
    print_queue(q, "Q");
    try_step("ENQUEUE(Q, 40)", [&q] { enqueue(q, 40); });

    const int first = dequeue(q);
    const int second = dequeue(q);
    print_step("DEQUEUE вернула " + std::to_string(first) + ", затем " + std::to_string(second));
    enqueue(q, 40);
    enqueue(q, 50);
    print_step("ENQUEUE 40, 50 — tail переходит через конец массива на начало");
    print_queue(q, "Q");
    try_step("ENQUEUE(Q, 60)", [&q] { enqueue(q, 60); });

    while (!queue_empty(q)) {
        print_step("DEQUEUE(Q) вернула " + std::to_string(dequeue(q)));
    }
    print_queue(q, "Q");
    try_step("DEQUEUE(Q) на пустой очереди", [&q] { dequeue(q); });
    std::cout << '\n';
}

void run_task_10_1_5() {
    print_title("Задание 10.1.5. Дек на массиве D[1..6]");
    print_legend();
    Deque d = make_deque(kArraySize);
    print_deque(d, "D");

    push_back(d, 4);
    push_back(d, 1);
    print_step("PUSH-BACK(D, 4), PUSH-BACK(D, 1)");
    print_deque(d, "D");

    push_front(d, 3);
    print_step("PUSH-FRONT(D, 3) — head уходит с 1 на 6 (по кругу)");
    print_deque(d, "D");

    push_front(d, 8);
    print_step("PUSH-FRONT(D, 8)");
    print_deque(d, "D");

    int value = pop_back(d);
    print_step("POP-BACK(D) вернула " + std::to_string(value));
    print_deque(d, "D");

    value = pop_front(d);
    print_step("POP-FRONT(D) вернула " + std::to_string(value));
    print_deque(d, "D");

    std::cout << "Порядок элементов от головы к хвосту: ";
    while (!deque_empty(d)) {
        std::cout << pop_front(d) << ' ';
    }
    std::cout << '\n';
    try_step("POP-BACK(D) на пустом деке", [&d] { pop_back(d); });
    std::cout << '\n';
}

void run_all_tasks() {
    run_task_10_1_1();
    run_task_10_1_2();
    run_task_10_1_3();
    run_task_10_1_4();
    run_task_10_1_5();
}

bool run_task(const std::string& number) {
    const std::pair<const char*, void (*)()> table[] = {{"10.1.1", run_task_10_1_1},
                                                        {"10.1.2", run_task_10_1_2},
                                                        {"10.1.3", run_task_10_1_3},
                                                        {"10.1.4", run_task_10_1_4},
                                                        {"10.1.5", run_task_10_1_5}};
    for (const auto& [name, task] : table) {
        if (number == name) {
            task();
            return true;
        }
    }
    return false;
}

}  // namespace sem9
