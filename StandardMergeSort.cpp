#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "StandardMergeSort.h"
#include "CompareStrings.h"

void StandardMergeSort(std::vector<std::string> &strings,
                       int l,
                       int r,
                       std::vector<std::string> &temp,
                       int &comparisonCount) {
  // Неспециализированный MergeSort на отрезке [l; r]. Использует посимвольное (неоптимизированное) сравнение
  if (l < r) {
    int mid = l + (r - l) / 2;
    StandardMergeSort(strings, l, mid, temp, comparisonCount);
    StandardMergeSort(strings, mid + 1, r, temp, comparisonCount);

    // Слияние двух отсортированных половин
    int i = l;
    int j = mid + 1;
    int k = l;
    while (i <= mid && j <= r) {
      if (CompareStrings(strings[i], strings[j], comparisonCount)) {
        temp[k++] = strings[i++];
      } else {
        temp[k++] = strings[j++];
      }
    }
    while (i <= mid) {
      temp[k++] = strings[i++];
    }
    while (j <= r) {
      temp[k++] = strings[j++];
    }

    // Копируем обратно в исходный массив
    for (i = l; i <= r; ++i) {
      strings[i] = temp[i];
    }
  }
}

void StandardMergeSort(std::vector<std::string> &strings, int &comparisonCount) {
  // Начинаем с общего отрезка [0; n-1]
  int n = strings.size();
  std::vector<std::string> temp(n);
  StandardMergeSort(strings, 0, n - 1, temp, comparisonCount);
}