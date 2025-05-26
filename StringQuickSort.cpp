#include <string>
#include <vector>
#include <random>
#include "StringQuickSort.h"

namespace {

inline char GetCharAt(const std::string &str, int position) {
  // Возвращает символ на позиции `position`, либо '\0', если строка короче
  return (position < static_cast<int>(str.size()) ? str[position] : '\0');
}

void StringQuickSort(std::vector<std::string> &strings,
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

} // namespace

void StringQuickSort(std::vector<std::string> &strings, int &comparisonCount) {
  // Специализированный StringQuickSort для строк с учетом префиксов
  if (strings.size() <= 1) {
    return;
  }
  std::mt19937 gen(std::random_device{}());
  StringQuickSort(strings, 0, static_cast<int>(strings.size()) - 1, 0, gen, comparisonCount);
}
