#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "StringMergeSort.h"

struct Node { const std::string *str; int lcp; };

std::pair<char, int> LcpCompare(const std::string &a, const std::string &b, int offset, int &comparisonCount) {
  int i = offset;
  while (i < a.size() && i < b.size() && a[i] == b[i]) {
    ++comparisonCount;
    ++i;
  }
  ++comparisonCount;
  if (i == a.size() || i == b.size()) {
    return {'=', i};
  }
  ++comparisonCount;
  return {a[i] < b[i] ? '<' : '>', i};
}

void Merge(std::vector<Node> &nodes, int left, int mid, int right, std::vector<Node> &temp, int &comparisonCount) {
  // копируем в temp слева
  for (int i = left; i <= mid; ++i)
    temp[i] = nodes[i];
  // копируем в temp справа (сдвинув индекс)
  for (int j = mid + 1; j <= right; ++j)
    temp[j] = nodes[j];

  int i = left, j = mid + 1, k = left;

  while (i <= mid && j <= right) {
    int ki = temp[i].lcp;
    int pj = temp[j].lcp;

    if (ki > pj) {
      // первый префикс длиннее → строка L[i] уже точно "меньше"
      nodes[k++] = temp[i++];
    } else if (ki < pj) {
      // второй префикс длиннее → строка R[j] уже точно "меньше"
      nodes[k++] = temp[j++];
    } else {
      // ki == pj → надо точное сравнение с позиции ki
      auto [cmp, h] = LcpCompare(*temp[i].str, *temp[j].str, ki, comparisonCount);
      if (cmp == '<') {
        // L[i] < R[j]
        nodes[k++] = {temp[i].str, ki};
        // Обновляем LCP для R[j], чтобы в дальнейшем не пересчитывать первые h символов
        temp[j].lcp = h;
        ++i;
      } else {
        // R[j] <= L[i]
        nodes[k++] = {temp[j].str, pj};
        // Обновляем LCP для L[i]
        temp[i].lcp = h;
        ++j;
      }
    }
  }

  // Оставшиеся элементы
  while (i <= mid) {
    nodes[k++] = temp[i++];
  }
  while (j <= right) {
    nodes[k++] = temp[j++];
  }
}

void StringMergeSort(std::vector<Node> &nodes, int left, int right, std::vector<Node> &temp, int &comparisonCount) {
  // Специализированный MergeSort для строк с учётом LCP на отрезке [left; right]
  if (left == right) {
    // Одна строка — её LCP с предыдущей считается = 0
    nodes[left].lcp = 0;
    return;
  }

  int mid = (left + right) / 2;
  StringMergeSort(nodes, left, mid, temp, comparisonCount);
  StringMergeSort(nodes, mid + 1, right, temp, comparisonCount);
  // Сливаем две половины
  Merge(nodes, left, mid, right, temp, comparisonCount);
}

void StringMergeSort(std::vector<std::string> &strings, int &comparisonCount) {
  // Специализированный MergeSort для строк с учётом LCP
  int n = strings.size();
  std::vector<Node> nodes(n);

  for (int i = 0; i < n; ++i) {
    nodes[i] = {&strings[i], 0};
  }

  std::vector<Node> temp(n); // Временный массив для слияния

  StringMergeSort(nodes, 0, n - 1, temp, comparisonCount);

  std::vector<std::string> output(n);

  for (int i = 0; i < n; ++i) {
    output[i] = *nodes[i].str; // Извлекаем отсортированные строки
  }
  strings = std::move(output); // Перемещаем отсортированные строки обратно в исходный вектор
}