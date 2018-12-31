#include <regex>

#include <crombie2/Cut.h>

using namespace crombie2;

Cut::Cut (const std::string& cut) {
  set(cut);
}


std::string Cut::label () const {

  if (is_literal()) {
    // An expression for finding the left hand side of a cut
    std::regex lhs {"([^=<>]+?)\\s*[=<>]+.*"};
    std::smatch matches;
    std::regex_search(value, matches, lhs);
    return matches[1];
  }
  return "SUB";

}


std::string Cut::get () const {

  if (is_literal()) {
    return std::string("'") + value + "'";
  }
  return value;

}


void Cut::set (const std::string& input) {

  literal = (input[0] == '\'');

  value = literal
    ? input.substr(1, input.size() - 2)
    : input;

}


bool Cut::is_literal () const {

  return literal;

}


std::string Cut::cut () const {

  if (value[0] != '!' and value.size())
    return value;
  return "1";

}
