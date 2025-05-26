#ifndef A1_9_AISD__STRINGSORTTESTER_H_
#define A1_9_AISD__STRINGSORTTESTER_H_

#include "StringGenerator.h"

#include <vector>
#include <string>

class StringSortTester {
  using SortFunc = void (*)(std::vector<std::string> &, int &);

  StringGenerator _stringGenerator;

 public:
  StringSortTester();
  void TestSortingAlgorithms(SortFunc sortFunc, std::string const &path);
};

#endif //A1_9_AISD__STRINGSORTTESTER_H_
