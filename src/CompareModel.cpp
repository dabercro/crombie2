#include <regex>

#include <crombie2/CompareModel.h>


using namespace crombie2;


std::string CompareModel::get_name () const {
  return "compare";
}


void CompareModel::read (const Types::strings& config) {
  list.clear();

  std::regex expr {"'([^']+)';\\s*([^;]+);\\s*(\\d+)"};
  std::smatch matches;

  for (auto& line : config) {
    if (std::regex_match(line, matches, expr)) {
      auto& compare = add();
      for (unsigned imatch = 0; imatch < 3; imatch++)
        compare.get_confs()[imatch]->set(matches[imatch + 1]);

    }
  }

}


std::list<std::string> CompareModel::serialize () const {

  std::list<std::string> output {};

  for (auto& compare : list) {
    if (not compare.name.get().size())
      continue;

    std::string line =
      std::string("'") +
      compare.name.get() + "'; " +
      compare.legend.get() + "; " +
      compare.style.get();
    output.push_back(line);
  }

  return output;

}
