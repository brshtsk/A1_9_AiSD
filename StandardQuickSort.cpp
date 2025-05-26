#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "StandardQuickSort.h"
#include "CompareStrings.h"

int Partition(std::vector<std::string> &strings, int l, int r, int pivotIndex, int &comparisonCount) {
  // Поменяли pivot с концом, потом поставим его на StoreIndex
  swap(strings[pivotIndex], strings[r]);
  std::string pivot = strings[r];
  int storeIndex = l; // Объекты [l; StoreIndex) всегда меньше pivot

  for (int i = l; i < r; ++i) {
    if (CompareStrings(strings[i], pivot, comparisonCount)) {
      std::swap(strings[storeIndex], strings[i]);
      storeIndex++;
    }
  }

  std::swap(strings[storeIndex], strings[r]);
  // Теперь все элементы [l; StoreIndex) меньше pivot, а [StoreIndex + 1; r] больше
  return storeIndex;
}

void StandardQuickSort(std::vector<std::string> &strings, int l, int r, std::mt19937 &gen, int &comparisonCount) {
  // Неспециализированный QuickSort на отрезке [l; r]. Использует посимвольное (неоптимизированное) сравнение
  if (l < r) {
    // Генератор случайных чисел для выбора опорного элемента
    std::uniform_int_distribution<int> dist(l, r);
    int pivotIndex = dist(gen);
    int newPivotIndex = Partition(strings, l, r, pivotIndex, comparisonCount);
    // Рекурсивно сортируем две части
    StandardQuickSort(strings, l, newPivotIndex - 1, gen, comparisonCount);
    StandardQuickSort(strings, newPivotIndex + 1, r, gen, comparisonCount);
  }
}

void StandardQuickSort(std::vector<std::string> &strings, int &comparisonCount) {
  // Начинаем с общего отрезка [0; n-1]
  std::mt19937 gen(std::random_device{}());
  if (!strings.empty()) {
    StandardQuickSort(strings, 0, strings.size() - 1, gen, comparisonCount);
  }
}