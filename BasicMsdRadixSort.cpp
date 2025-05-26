#include <vector>
#include <string>
#include <random>
#include <array>
#include "BasicMsdRadixSort.h"

void BasicMsdRadixSort(std::vector<std::string_view> &strings,
                       int generalPrefix,
                       int &comparisonCount,
                       std::vector<std::string_view> &excl) {
  // Базовая реализация MSD Radix Sort для строк (без перехода на StringQuickSort)
  if (strings.size() <= 1) {
    return; // Если массив пуст или все строки уже отсортированы
  }

  excl.clear();
  std::array<std::vector<std::string_view>, 128> buckets;

  for (const auto &str : strings) {
    if (str.size() <= generalPrefix) {
      excl.push_back(str); // Сохраняем короткие строки
    } else {
      char c = str[generalPrefix];
      ++comparisonCount; // Считаем нахождение бакета "сравнением"
      buckets[static_cast<unsigned char>(c)].push_back(str); // Размещаем в соответствующий bucket
    }
  }

  int n = strings.size();
  strings.clear();
  strings.reserve(n);
  strings.insert(strings.end(), excl.begin(), excl.end());

  for (int i = 0; i < 128; ++i) {
    if (!buckets[i].empty()) {
      // Рекурсивно сортируем строки в текущем bucket
      BasicMsdRadixSort(buckets[i], generalPrefix + 1, comparisonCount, excl);
      strings.insert(strings.end(), buckets[i].begin(), buckets[i].end());
    }
  }
}

void BasicMsdRadixSort(std::vector<std::string> &strings, int &comparisonCount) {
  // Начинаем с общего префикса 0
  std::vector<std::string_view> views;
  views.reserve(strings.size());
  for (auto &s : strings) {
    views.emplace_back(s);
  }

  std::vector<std::string_view> excl;
  excl.reserve(strings.size());

  BasicMsdRadixSort(views, 0, comparisonCount, excl);

  std::vector<std::string> result;
  result.reserve(strings.size());
  for (auto sv : views) {
    result.emplace_back(sv);  // копируем каждый отсортированный view в новый string
  }

  strings = std::move(result); // перемещаем результат обратно в исходный вектор
}