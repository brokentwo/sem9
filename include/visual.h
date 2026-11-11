#pragma once
#include <optional>
#include <string>
#include <vector>

namespace sem9 {

// Ячейка массива: std::nullopt — в ячейку ещё ничего не записывали.
using Cell = std::optional<int>;

// Подпись-стрелка под массивом, например {"S.top", 3}.
struct Marker {
    std::string label;
    int index;
};

// Печатает массив cells[1..n] в стиле рис. 10.1 и 10.2:
//   [  4] — ячейка принадлежит структуре (на рисунке светло-серая),
//   (  3) — значение лежит в массиве, но структуре уже не принадлежит (тёмная),
//   (   ) — в ячейку ещё ничего не записывали.
// cells и active индексируются с 1 (элемент [0] не используется).
// Под массивом рисуются стрелки ^ к ячейкам из markers и их подписи.
void print_array(const std::string& name, const std::vector<Cell>& cells,
                 const std::vector<bool>& active, const std::vector<Marker>& markers);

// Печатает пояснение к обозначениям ячеек.
void print_legend();

}  // namespace sem9
