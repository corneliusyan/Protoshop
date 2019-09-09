#include "string.hpp"
#include <iostream>

// https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
bool hasEnding(std::string const& fullString, std::string const& ending) {
  if (fullString.length() >= ending.length()) {
    int compareEnding = fullString.compare(
      fullString.length() - ending.length(),
      ending.length(),
      ending
    );
    return 0 == compareEnding;
  }
  return false;
}
