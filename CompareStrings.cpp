#include "CompareStrings.h"

#include <string>
#include <vector>

bool CompareStrings(std::string const &a, std::string const &b, int &comparisonCount) {
  // Сравниваем строки посимвольно, увеличивая счетчик сравнений
  for (size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
    ++comparisonCount;
    if (a[i] != b[i]) {
      return a[i] < b[i];
    }
  }
  ++comparisonCount;
  // Если строки равны до min(a.size(), b.size()), то сравниваем по длине
  return a.size() < b.size();
}
