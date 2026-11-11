#include <iostream>

#include "tasks.h"

// Без аргументов — все задания подряд; ./sem9 10.1.3 — только одно задание.
int main(int argc, char** argv) {
    if (argc < 2) {
        sem9::run_all_tasks();
        return 0;
    }
    if (!sem9::run_task(argv[1])) {
        std::cerr << "Нет такого задания: " << argv[1] << " (есть 10.1.1 ... 10.1.5)\n";
        return 1;
    }
    return 0;
}
