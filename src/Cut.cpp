#include <regex>

#include "crombie2/Cut.h"

using namespace crombie2;

Cut::Cut(const std::string& cut) :
  Configurable<std::string>(
    [] (auto& c) {
      // An expression for finding the left hand side of a cut
      std::regex lhs {"([^=<>]+?)\\s*[=<>]+.*"};
      std::smatch matches;
      std::regex_search(c, matches, lhs);
      return matches[1];
    },
    cut)
{}
