#ifndef A1_9_AISD__STRINGGENERATOR_H_
#define A1_9_AISD__STRINGGENERATOR_H_

#include <string>
#include <vector>
#include <random>

class StringGenerator {
  inline static constexpr std::string_view allowed_chars =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789"
      "!@#%:;^&*()-";

 public:
  StringGenerator();

  enum GenerationMode {
    RANDOM,
    REVERSED,
    ALMOST_SORTED,
    MATCHING_PREFIX
  };

  std::vector<std::string> GetStrings(int count, GenerationMode mode);

 private:
  std::vector<std::string> _randomStrings;
  std::vector<std::string> _reversedStrings;
  std::vector<std::string> _almostSortedStrings;
  std::vector<std::string> _matchingPrefixStrings;

  std::string GenerateRandomString(int length);

  std::mt19937 generator;
};

#endif //A1_9_AISD__STRINGGENERATOR_H_
