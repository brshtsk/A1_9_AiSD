#include "StringSortTester.h"
#include "StringGenerator.h"
#include <fstream>
#include <iostream>
#include <chrono>

StringSortTester::StringSortTester() : _stringGenerator() {}

void StringSortTester::TestSortingAlgorithms(StringSortTester::SortFunc sortFunc, const std::string &path) {
  /* Формат строк файла:
   * <вид генерации массива> <размер массива> <время выполнения (мкс)> <количество сравнений>
   */
  std::ofstream file(path, std::ios::trunc);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file for writing: " + path);
  }

  std::cout << std::endl << "Begin testing for " << path << std::endl;

  for (auto mode : {StringGenerator::RANDOM, StringGenerator::REVERSED, StringGenerator::ALMOST_SORTED,
                    StringGenerator::MATCHING_PREFIX}) {
    std::cout << "Testing mode: " << mode << std::endl;

    for (int size = 100; size <= 3000; size += 100) {
      int comparisonCount = 0;
      auto strings = _stringGenerator.GetStrings(size, mode);

      auto start = std::chrono::high_resolution_clock::now();
      sortFunc(strings, comparisonCount);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

      std::string modeStr;
      switch (mode) {
        case StringGenerator::RANDOM: modeStr = "RANDOM";
          break;
        case StringGenerator::REVERSED: modeStr = "REVERSED";
          break;
        case StringGenerator::ALMOST_SORTED: modeStr = "ALMOST_SORTED";
          break;
        case StringGenerator::MATCHING_PREFIX: modeStr = "MATCHING_PREFIX";
          break;
      }

      file << modeStr << " " << size << " " << duration << " " << comparisonCount << "\n";
    }
  }

  file.close();
  std::cout << "Finished tests for " << path << std::endl;
}
