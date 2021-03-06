#include <regex>

#include <crombie2/CutModel.h>
#include <crombie2/Misc.h>


using namespace crombie2;


std::string CutModel::get_name () const {
  return "cuts";
}


void CutModel::read (const Types::strings& config) {

  selections.clear();
  cutstrings.clear();

  // This is used to select lines that describe a cut at the end
  std::regex selectionline{"^:\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s*([^\\s,]*)\\s*(,\\s*(\\S*))?\\s*$"};

  // This is used to get a label for a cutstring
  std::regex labelline{"^LABEL:\\s(.*)$"};

  // This is used to read all other (non-empty) lines
  std::regex expr{"^(\\S*)\\s*([^\\s\\']*)\\s+(\\S.*)$"};

  std::smatch matches;

  CutString* last_cutstring {};

  for (auto& line : config) {
    if (std::regex_search(line, matches, selectionline))
      selections.append(matches[1], matches[2], matches[3], matches[4], matches[6]);

    else if (std::regex_search(line, matches, labelline)) {
      if (not last_cutstring)
        throw std::runtime_error {"Setting LABEL, but no cutstring yet!"};

      last_cutstring->label.set(matches[1]);
    }

    else if (std::regex_search(line, matches, expr)) {
      // Add a cutstring into the map and get a pointer to it
      if (matches[1].length())
        last_cutstring = &add_cutstring(matches[1], matches[2]);

      last_cutstring->add_cut().set(matches[3]);
    }
  }

}


RemoveWrapper<CutModel::cutstype>& CutModel::add_cutstring (const std::string& label, const std::string& joiner) {

  return cutstrings.append(cutstype(label, joiner));

}


std::list<std::string> CutModel::serialize () const {

  std::list<std::string> output {};

  for (const auto& cutstring : cutstrings) {
    if (not cutstring.name.get().size())
      continue;

    std::string line = cutstring.name.get() +
      " " + cutstring.joiner.get() + " ";

    for (auto& cut : cutstring.get_cuts()) {
      if (cut.get().size()) {
        line += cut.get();
        output.push_back(line);
        line = "    ";
      }
    }

    if (cutstring.label.get().size())
      output.push_back(std::string("LABEL: ") + cutstring.label.get());
  }

  for (auto& selection : selections) {
    if (selection.cut.get().size())
      output.push_back(std::string(": ") +
                       selection.cut.get() + " " +
                       selection.data_weight.get() + " " +
                       selection.mc_weight.get() + " " +
                       selection.name.get() + ", " +
                       selection.control_plot.get());
  }

  return output;

}


std::string CutModel::expand (const std::string& cutlabel) const {

  bool negate = cutlabel.size() and cutlabel[0] == '!';

  std::string output {negate ? "!(" : "("};
  std::string label {cutlabel.data() + negate};

  // We use a pointer here to escape the try-block scope
  // There should be no way to be invalid without throwing an exception
  const CutString* cutstring {nullptr};
  try {
    cutstring = &at(label);
  }
  catch (const std::exception& e) {
    Misc::message(e.what(), std::string("Key \"") + label + "\" does not seem to be in the map");
    throw;
  }

  const std::string& joiner = cutstring->joiner.get();

  for (auto& cut : cutstring->get_cuts()) {

    if (cut.get() == label)
      throw std::runtime_error {label + " is requiring itself."};

    // Skip over empty cuts
    if (cut.cut() == "1")
      continue;

    if (output.back() != '(')
      output += std::string(" ") + joiner + " ";
    output += cut.is_literal()
      ? cut.cut()
      : expand(cut.get());

  }

  if (output.back() == '(')
    output += "1";

  output += ")";

  return output;

}


std::list<std::string> CutModel::get_labels () const {

  std::list<std::string> output {};
  for (auto& cut : cutstrings)
    output.emplace_back(cut.name);

  return output;

}


RemoveWrapper<CutString>& CutModel::get_cutstring (const std::string& label) {

  return at(label);

}


bool CutModel::is_valid () const {

  try {
    for (auto& selection : selections) {
      expand(selection.cut);
      expand(selection.data_weight);
      expand(selection.mc_weight);
    }
  }
  catch (const std::exception& e) {
    return false;
  }

  return true;

}

bool CutModel::is_valid (Tree& tree, bool skip_branch_check) const {

  try {
    for (auto& selection : selections) {
      if (not tree.is_valid(expand(selection.cut)) or
          not (skip_branch_check or tree.is_valid(expand(selection.data_weight))) or
          not (skip_branch_check or tree.is_valid(expand(selection.mc_weight))))
        return false;
    }
  }
  catch (const std::exception& e) {
    return false;
  }

  return true;

}


std::vector<std::string> CutModel::cutflow (const std::string& label) const {

  std::vector<std::string> output {};

  // If not a good label or model, just abandon
  if (not is_valid() or not label.size())
    return output;

  // If a negation operator in front, just send it back
  if (label.front() == '!')
    output.push_back(expand(label));

  else {
    auto& cutstring = at(label);
    // If not joined by &&, send back
    if (cutstring.joiner.get() != "&&")
      output.push_back(expand(label));
    else {
      // For each cut, add literals and expand labels
      for (auto& cut : cutstring.get_cuts()) {
        if (cut.cut() == "1")
          continue;

        if (cut.is_literal())
          output.push_back(cut.cut());
        else {
          auto expanded = cutflow(cut.get());
          output.insert(output.end(), expanded.begin(), expanded.end());
        }
      }
    }
  }

  return output;

}


const RemoveWrapper<CutString>& CutModel::at (const std::string& label) const {

  for (const auto& cut : cutstrings)
    if (cut.name.get() == label)
      return cut;

  throw std::runtime_error {label + " does not exist in CutModel"};

}


RemoveWrapper<CutString>& CutModel::at (const std::string& label) {

  for (auto& cut : cutstrings)
    if (cut.name.get() == label)
      return cut;

  throw std::runtime_error {label + " does not exist in CutModel"};

}


std::vector<std::string> CutModel::labels (const std::string& label) const {

  std::vector<std::string> output {};


  // Need a recursive way to add
  std::function<void(const std::string&)> add_to_output;

  add_to_output = [this, &output, &add_to_output] (const std::string& nextlabel) {
    if (nextlabel.front() == '!')
      return;

    auto& cutstring = at(nextlabel);
    auto toadd = cutstring.label.get();
    if (toadd.size())
      output.emplace_back(toadd);

    for (auto& cut : cutstring.get_cuts()) {
      if (not cut.is_literal())
        add_to_output(cut.get());
    }

  };

  add_to_output(label);

  return output;

}
