#include <regex>

#include <crombie2/OnTheFlyModel.h>


using namespace crombie2;


std::string OnTheFlyModel::get_name () const {
  return "onthefly";
}


void OnTheFlyModel::read (const Types::strings& config) {
  list.clear();

  std::regex expr {"([^,]*),\\s*([^,]*),\\s*([^,]*),\\s*(.*)"};
  std::smatch matches;

  for (auto& line : config) {
    if (std::regex_match(line, matches, expr)) {

      auto& reweight = add();
      for (unsigned imatch = 0; imatch < 4; imatch++)
        reweight.table.get_confs()[imatch]->set(matches[imatch + 1]);

    }
  }

}


std::list<std::string> OnTheFlyModel::serialize () const {

  std::list<std::string> output {};

  for (auto& reweight : list) {

    std::string line =
      reweight.expr.get() + "', " +
      reweight.cut.get() + ", " +
      reweight.file.get() + ", " +
      reweight.hist.get();

    output.push_back(line);

  }

  return output;

}
