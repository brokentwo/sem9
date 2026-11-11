#include "visual.h"

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace sem9 {

namespace {

constexpr int kCellWidth = 5;   // ширина одной ячейки: "[  4]"
constexpr int kNameWidth = 4;   // ширина колонки с именем массива
constexpr int kValueWidth = 3;  // ширина числа внутри ячейки

// Номер столбца (от начала строки), под которым находится центр ячейки index.
int column_of(int index) {
    if (index < 1) {
        return kNameWidth - 2;  // пустой стек: стрелка левее массива
    }
    return kNameWidth + (index - 1) * kCellWidth + kCellWidth / 2;
}

std::string format_cell(const Cell& cell, bool is_active) {
    std::ostringstream out;
    out << (is_active ? '[' : '(');
    if (cell.has_value()) {
        out << std::setw(kValueWidth) << *cell;
    } else {
        out << std::string(kValueWidth, ' ');
    }
    out << (is_active ? ']' : ')');
    return out.str();
}

// Дописывает text в строку line, начиная со столбца col (или правее, если занято).
void place_text(std::string& line, int col, const std::string& text) {
    std::size_t start = static_cast<std::size_t>(std::max(col, 0));
    if (!line.empty() && start < line.size() + 2) {
        start = line.size() + 2;
    }
    if (line.size() < start) {
        line.append(start - line.size(), ' ');
    }
    line += text;
}

}  // namespace

void print_array(const std::string& name, const std::vector<Cell>& cells,
                 const std::vector<bool>& active, const std::vector<Marker>& markers) {
    const int n = static_cast<int>(cells.size()) - 1;

    // строка с номерами ячеек
    std::cout << std::string(kNameWidth, ' ');
    for (int i = 1; i <= n; ++i) {
        std::cout << std::setw(kCellWidth - 1) << i << ' ';
    }
    std::cout << '\n';

    // сами ячейки
    std::cout << std::left << std::setw(kNameWidth) << name << std::right;
    for (int i = 1; i <= n; ++i) {
        const bool is_active = static_cast<std::size_t>(i) < active.size() && active[i];
        std::cout << format_cell(cells[i], is_active);
    }
    std::cout << '\n';

    // стрелки и подписи
    std::vector<Marker> sorted = markers;
    std::sort(sorted.begin(), sorted.end(),
              [](const Marker& a, const Marker& b) { return a.index < b.index; });
    std::string arrows;
    std::string labels;
    for (const Marker& m : sorted) {
        const int col = column_of(m.index);
        if (static_cast<int>(arrows.size()) <= col) {
            arrows.append(static_cast<std::size_t>(col) - arrows.size(), ' ');
            arrows += '^';
        }
        place_text(labels, col - 2, m.label + " = " + std::to_string(m.index));
    }
    std::cout << arrows << '\n' << labels << "\n\n";
}

void print_legend() {
    std::cout << "Обозначения: [  4] — элемент структуры, (  3) — значение осталось в массиве,\n"
                 "             но структуре не принадлежит, (   ) — ячейка ещё не заполнялась.\n\n";
}

}  // namespace sem9
