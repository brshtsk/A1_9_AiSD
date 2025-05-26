#include "StringSortTester.h"
#include <iostream>
#include "StandardQuickSort.h"
#include "StandardMergeSort.h"
#include "StringQuickSort.h"
#include "StringMergeSort.h"
#include "BasicMsdRadixSort.h"
#include "BoostedMsdRadixSort.h"

std::string const PREFIX = R"(C:\Users\kitki\CLionProjects\hse\A1_9_AiSD\results\)";

int main() {

  StringSortTester tester;

  std::cout << "Begin tests..." << std::endl;

  for (int i = 1; i <= 5; ++i) {
    std::cout << std::endl << "##########" << std::endl << "Test #" << i << std::endl << "##########" << std::endl;

    std::string testNum = std::to_string(i);
    tester.TestSortingAlgorithms(StandardQuickSort, PREFIX + "StandardQuickSort.txt" + testNum);
    tester.TestSortingAlgorithms(StandardMergeSort, PREFIX + "StandardMergeSort.txt" + testNum);
    tester.TestSortingAlgorithms(StringQuickSort, PREFIX + "StringQuickSort.txt" + testNum);
    tester.TestSortingAlgorithms(StringMergeSort, PREFIX + "StringMergeSort.txt" + testNum);
    tester.TestSortingAlgorithms(BasicMsdRadixSort, PREFIX + "BasicMsdRadixSort.txt" + testNum);
    tester.TestSortingAlgorithms(BoostedMsdRadixSort, PREFIX + "BoostedMsdRadixSort.txt" + testNum);
  }

  std::cout << "All tests done." << std::endl;
  return 0;
}