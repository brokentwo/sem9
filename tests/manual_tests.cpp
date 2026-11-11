// Проверочные сценарии: типичные случаи, граничные случаи и ошибки.
#include <iostream>
#include <stdexcept>
#include <string>

#include "deque.h"
#include "queue.h"
#include "stack.h"
#include "two_stacks.h"

namespace {

int g_failed = 0;

void check(bool condition, const std::string& name) {
    std::cout << (condition ? "[ OK ] " : "[FAIL] ") << name << '\n';
    if (!condition) {
        ++g_failed;
    }
}

// true, если action бросает исключение типа E.
template <typename E, typename F>
bool throws(F action) {
    try {
        action();
    } catch (const E&) {
        return true;
    } catch (...) {
        return false;
    }
    return false;
}

void test_stack() {
    sem9::Stack s = sem9::make_stack(6);
    sem9::push(s, 4);
    sem9::push(s, 1);
    sem9::push(s, 3);
    const int a = sem9::pop(s);
    sem9::push(s, 8);
    const int b = sem9::pop(s);
    check(a == 3 && b == 8 && s.top == 2 && *s.data[1] == 4 && *s.data[2] == 1,
          "10.1.1: после PUSH 4,1,3, POP, PUSH 8, POP в стеке 4, 1, S.top = 2");
    check(*s.data[3] == 8, "10.1.1: снятое значение 8 осталось в S[3]");

    sem9::Stack empty = sem9::make_stack(1);
    check(throws<std::underflow_error>([&] { sem9::pop(empty); }),
          "стек: POP пустого -> underflow");
    sem9::push(empty, 5);
    check(throws<std::overflow_error>([&] { sem9::push(empty, 6); }),
          "стек: PUSH в полный -> overflow");
    check(throws<std::invalid_argument>([] { sem9::make_stack(0); }),
          "стек: размер 0 -> invalid_argument");
}

void test_two_stacks() {
    sem9::TwoStacks s = sem9::make_two_stacks(5);
    for (int i = 0; i < 4; ++i) {
        sem9::push1(s, i);
    }
    sem9::push2(s, 100);
    check(sem9::size1(s) == 4 && sem9::size2(s) == 1,
          "10.1.2: стек 1 занял 4 ячейки из 5, стек 2 — 1");
    check(throws<std::overflow_error>([&] { sem9::push2(s, 7); }),
          "10.1.2: переполнение только при 5 элементах в сумме");
    check(sem9::pop2(s) == 100 && sem9::pop1(s) == 3,
          "10.1.2: каждый стек отдаёт свой верхний элемент");
    check(throws<std::underflow_error>([&] { sem9::pop2(s); }),
          "10.1.2: POP2 пустого стека 2 -> underflow");
}

void test_queue() {
    sem9::Queue q = sem9::make_queue(6);
    sem9::enqueue(q, 4);
    sem9::enqueue(q, 1);
    sem9::enqueue(q, 3);
    const int a = sem9::dequeue(q);
    sem9::enqueue(q, 8);
    const int b = sem9::dequeue(q);
    check(a == 4 && b == 1 && q.head == 3 && q.tail == 5 && sem9::queue_size(q) == 2,
          "10.1.3: после операций в очереди 3, 8; head = 3, tail = 5");

    sem9::Queue small = sem9::make_queue(3);
    check(throws<std::underflow_error>([&] { sem9::dequeue(small); }),
          "10.1.4: DEQUEUE пустой -> underflow");
    sem9::enqueue(small, 1);
    sem9::enqueue(small, 2);
    check(sem9::queue_full(small), "10.1.4: Q[1..3] полна после 2 элементов");
    check(throws<std::overflow_error>([&] { sem9::enqueue(small, 3); }),
          "10.1.4: ENQUEUE в полную -> overflow");
    sem9::dequeue(small);
    sem9::enqueue(small, 3);  // tail проходит через конец массива
    check(sem9::dequeue(small) == 2 && sem9::dequeue(small) == 3 && sem9::queue_empty(small),
          "10.1.4: порядок FIFO сохраняется при переходе через конец массива");
    check(throws<std::invalid_argument>([] { sem9::make_queue(1); }),
          "очередь: длина 1 -> invalid_argument");
}

void test_deque() {
    sem9::Deque d = sem9::make_deque(4);
    sem9::push_back(d, 2);
    sem9::push_front(d, 1);  // head уходит через начало массива на конец
    sem9::push_back(d, 3);
    check(sem9::deque_full(d), "10.1.5: D[1..4] полон после 3 элементов");
    check(throws<std::overflow_error>([&] { sem9::push_front(d, 0); }),
          "10.1.5: вставка в полный -> overflow");
    check(sem9::pop_front(d) == 1 && sem9::pop_back(d) == 3 && sem9::pop_back(d) == 2,
          "10.1.5: удаление с обоих концов в правильном порядке");
    check(throws<std::underflow_error>([&] { sem9::pop_front(d); }),
          "10.1.5: удаление из пустого -> underflow");
}

}  // namespace

int main() {
    test_stack();
    test_two_stacks();
    test_queue();
    test_deque();
    std::cout << (g_failed == 0 ? "\nВсе проверки пройдены\n" : "\nЕсть ошибки\n");
    return g_failed == 0 ? 0 : 1;
}
