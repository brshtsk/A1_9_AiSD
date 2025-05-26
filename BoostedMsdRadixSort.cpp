#include <vector>
#include <string>
#include <random>
#include <array>
#include "BoostedMsdRadixSort.h"

namespace sqs_view {

inline char GetCharAt(const std::string_view &str, int position) {
  // Возвращает символ на позиции `position`, либо '\0', если строка короче
  return (position < static_cast<int>(str.size()) ? str[position] : '\0');
}

void StringQuickSort(std::vector<std::string_view> &strings,
                     int left,
                     int right,
                     int currentPrefix,
                     std::mt19937 &gen,
                     int &comparisonCount) {
  if (left >= right) {
    return;
  }

  // Случайный выбор опорного символа на позиции currentPrefix
  std::uniform_int_distribution<int> distribution(left, right);
  int pivotIndex = distribution(gen);
  char pivotChar = GetCharAt(strings[pivotIndex], currentPrefix);

  int lessThanIndex = left;
  int greaterThanIndex = right;
  int currentIndex = left;

  while (currentIndex <= greaterThanIndex) {
    char currentChar = GetCharAt(strings[currentIndex], currentPrefix);

    ++comparisonCount;
    if (currentChar == pivotChar) {
      ++currentIndex;
    } else {
      ++comparisonCount;
      if (currentChar < pivotChar) {
        std::swap(strings[lessThanIndex++], strings[currentIndex++]);
      } else {
        std::swap(strings[currentIndex], strings[greaterThanIndex--]);
      }
    }
  }

  // Рекурсивно сортируем части
  StringQuickSort(strings, left, lessThanIndex - 1, currentPrefix, gen, comparisonCount);
  if (pivotChar != '\0') {
    StringQuickSort(strings, lessThanIndex, greaterThanIndex, currentPrefix + 1, gen, comparisonCount);
  }
  StringQuickSort(strings, greaterThanIndex + 1, right, currentPrefix, gen, comparisonCount);
}

void StringQuickSort(std::vector<std::string_view> &strings, int currentPrefix, int &comparisonCount) {
  // Специализированный StringQuickSort для строк с учетом префиксов
  if (strings.size() <= 1) {
    return;
  }
  std::mt19937 gen(std::random_device{}());
  StringQuickSort(strings, 0, static_cast<int>(strings.size()) - 1, currentPrefix, gen, comparisonCount);
}
} // namespace


void BoostedMsdRadixSort(std::vector<std::string_view> &strings,
                         int generalPrefix,
                         int &comparisonCount,
                         std::vector<std::string_view> &excl) {
  // Базовая реализация MSD Radix Sort для строк (без перехода на StringQuickSort)
  if (strings.size() <= 1) {
    return; // Если массив пуст или все строки уже отсортированы
  }

  if (strings.size() < 74) {
    sqs_view::StringQuickSort(strings, generalPrefix, comparisonCount);
    return;
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
      BoostedMsdRadixSort(buckets[i], generalPrefix + 1, comparisonCount, excl);
      strings.insert(strings.end(), buckets[i].begin(), buckets[i].end());
    }
  }
}

void BoostedMsdRadixSort(std::vector<std::string> &strings, int &comparisonCount) {
  // Начинаем с общего префикса 0
  std::vector<std::string_view> views;
  views.reserve(strings.size());
  for (auto &s : strings) {
    views.emplace_back(s);
  }

  std::vector<std::string_view> excl;
  excl.reserve(strings.size());

  BoostedMsdRadixSort(views, 0, comparisonCount, excl);

  std::vector<std::string> result;
  result.reserve(strings.size());
  for (auto sv : views) {
    result.emplace_back(sv);  // копируем каждый отсортированный view в новый string
  }

  strings = std::move(result); // перемещаем результат обратно в исходный вектор
}