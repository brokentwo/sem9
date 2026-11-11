cmake_minimum_required(VERSION 3.16)
project(sem9_stack_queue CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# общая библиотека: стек, два стека, очередь, дек и вывод массива
add_library(structures
    src/visual.cpp
    src/task_10_1_1_stack.cpp
    src/task_10_1_2_two_stacks.cpp
    src/task_10_1_3_queue.cpp
    src/task_10_1_4_queue_checked.cpp
    src/task_10_1_5_deque.cpp
    src/tasks.cpp)
target_include_directories(structures PUBLIC include)

# демонстрация заданий 10.1.1 - 10.1.5
add_executable(sem9 src/main.cpp)
target_link_libraries(sem9 PRIVATE structures)

# проверочные сценарии
add_executable(tests tests/manual_tests.cpp)
target_link_libraries(tests PRIVATE structures)
