#include "StringGenerator.h"

#include <random>
#include <algorithm>
#include <string>
#include <vector>

std::string StringGenerator::GenerateRandomString(int length) {
  std::string result;
  result.reserve(length);
  std::uniform_int_distribution<> distribution(0, allowed_chars.size() - 1);

  for (int i = 0; i < length; ++i) {
    result += allowed_chars[distribution(generator)];
  }
  return result;
}

StringGenerator::StringGenerator() {
  generator.seed(std::random_device{}());

  // В нем случайные строки
  _randomStrings.reserve(3000);

  for (int i = 0; i < 3000; ++i) {
    // Длина от 10 до 200
    int length = std::uniform_int_distribution<>(10, 200)(generator);
    _randomStrings.push_back(GenerateRandomString(length));
  }

  // В нем строки, но отсортированы в обратном порядке
  _reversedStrings = _randomStrings;
  std::sort(_reversedStrings.rbegin(), _reversedStrings.rend());

  // В нем строки почти отсортированные
  _almostSortedStrings = _randomStrings;
  std::sort(_almostSortedStrings.begin(), _almostSortedStrings.end());

  // Перемешаем ~10% пар строк, чтобы они не были полностью отсортированы
  for (int k = 0; k < 300; ++k) {
    int i = std::uniform_int_distribution<>(0, 2969)(generator);
    int j = i + std::uniform_int_distribution<>(1, 30)(generator);
    std::swap(_almostSortedStrings[i], _almostSortedStrings[j]);
  }

  // В нем строки, каждая имеет 1 из 4 возможных префиксов
  _matchingPrefixStrings.reserve(3000);

  // Создадим префиксы для строк (префиксы будут на 10-40 символов)
  std::vector<std::string> prefixes = {
      GenerateRandomString(10),
      GenerateRandomString(20),
      GenerateRandomString(30),
      GenerateRandomString(40)
  };

  for (int i = 0; i < 3000; ++i) {
    int prefixInd = std::uniform_int_distribution<>(0, prefixes.size() - 1)(generator);
    std::string prefix = prefixes[prefixInd];
    std::string randomPart = _randomStrings[i];
    std::string newString = prefix + randomPart;
    // Длина до 200
    if (newString.size() > 200) {
      newString = newString.substr(0, 200);
    }
    _matchingPrefixStrings.push_back(newString);
  }
}

std::vector<std::string> StringGenerator::GetStrings(int count, GenerationMode mode) {
  std::vector<std::string> result;

  switch (mode) {
    case RANDOM:result = _randomStrings;
      break;
    case REVERSED:result = _reversedStrings;
      break;
    case ALMOST_SORTED:result = _almostSortedStrings;
      break;
    case MATCHING_PREFIX:result = _matchingPrefixStrings;
      break;
  }

  if (count < result.size()) {
    result.resize(count);
  }

  return result;
}