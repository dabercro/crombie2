#include <regex>

#include <crombie2/CutModel.h>


using namespace crombie2;


std::string CutModel::get_name () const {
  return "cuts";
}


void CutModel::read (const Types::strings& config) {

  std::regex expr{"^(\\S*)\\s*([^\\s\\']*)\\s+(.+)$"};
  std::smatch matches;

  CutString* last_cutstring {};

  for (auto& line : config) {
    if (std::regex_search(line, matches, expr)) {
      if (matches[1].length()) {
        // Add a cutstring into the map and get a pointer to it
        last_cutstring = &(std::get<0>(
          cutstrings.insert(std::make_pair(std::string(matches[1]),
                                           CutString(matches[1], matches[2]))))->second);
        cutlabels.push_back(last_cutstring->name.get());
      }

      last_cutstring->add_cut().set(matches[2]);
    }
  }

}


std::list<std::string> CutModel::serialize () const {

  std::list<std::string> output {};

  for (auto& label : cutlabels) {
    const auto& cutstring = cutstrings.at(label);
    std::string line = cutstring.name.get() +
      " " + cutstring.joiner.get() + " ";

    for (auto& cut : cutstring.get_cuts()) {
      line += cut.get();
      output.push_back(line);
      line = "";
    }
  }

  return output;

}


std::string CutModel::expand (const std::string& cutlabel) const {

  std::string output {};

  const CutString& cutstring = cutstrings.at(cutlabel);
  const std::string& joiner = cutstring.joiner.get();

  for (auto& cut : cutstring.get_cuts()) {
    if (output.size())
      output += std::string(" ") + joiner + " ";
    output += cut.is_literal()
      ? cut.cut()
      : expand(cut.get());
  }

  return output;

}


const std::list<std::string>& CutModel::get_labels () const {
  return cutlabels;
}


const CutString& CutModel::get_cutstring (const std::string& label) const {
  return cutstrings.at(label);
}
