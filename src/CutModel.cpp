#include <regex>

#include <crombie2/CutModel.h>


using namespace crombie2;


std::string CutModel::get_name () const {
  return "cuts";
}


void CutModel::read (const Types::strings& config) {

  selections.clear();
  cutstrings.clear();
  cutlabels.clear();

  // This is used to select lines that describe a cut at the end
  std::regex selectionline{"^:\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s*$"};
  // This is used to read all other (non-empty) lines
  std::regex expr{"^(\\S*)\\s*([^\\s\\']*)\\s+(\\S.+)$"};

  std::smatch matches;

  CutString* last_cutstring {};

  for (auto& line : config) {
    if (std::regex_search(line, matches, selectionline))
      selections.emplace_back(matches[1], matches[2], matches[3]);

    else if (std::regex_search(line, matches, expr)) {
      // Add a cutstring into the map and get a pointer to it
      if (matches[1].length())
        last_cutstring = &add_cutstring(matches[1], matches[2]);

      last_cutstring->add_cut().set(matches[3]);
    }
  }

}


CutString& CutModel::add_cutstring (const std::string& label, const std::string& joiner) {

  auto inserted = cutstrings.insert(std::make_pair(label, CutString(label, joiner)));
  if (std::get<1>(inserted)) {

    auto& output = std::get<0>(inserted)->second;
    cutlabels.push_back(output.name.get());
    return output;

  }

   throw std::runtime_error{"Tried to add duplicate cut label."};

}


std::list<std::string> CutModel::serialize () const {

  std::list<std::string> output {};

  for (auto& label : cutlabels) {
    const auto& cutstring = cutstrings.at(label);
    if (not cutstring.name.get().size())
      continue;

    std::string line = cutstring.name.get() +
      " " + cutstring.joiner.get() + " ";

    for (auto& cut : cutstring.get_cuts()) {
      if (cut.get().size()) {
        line += cut.get();
        output.push_back(line);
      }
      line = "    ";
    }
  }

  for (auto& selection : selections) {
    if (selection.cut.get().size())
      output.push_back(std::string(": ") +
                       selection.cut.get() + " " +
                       selection.data_weight.get() + " " +
                       selection.mc_weight.get());
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


CutString& CutModel::get_cutstring (const std::string& label) {
  return cutstrings.at(label);
}
