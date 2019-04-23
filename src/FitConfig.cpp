#include <algorithm>
#include <regex>

#include <crombie2/FitConfig.h>


using namespace crombie2;


FitConfig::FitConfig (const std::string& expr) :
  Configurable<std::string>("Fit Expression", expr)
{

  // Hacky way to make sure the entry is filled
  get_widget();
  resize_guesses();

  // Change in the future too
  entry.signal_changed().connect(sigc::mem_fun(*this, &FitConfig::resize_guesses));

}


void FitConfig::resize_guesses () {

  const std::string formula = entry.get_chars(0, -1);

  std::regex index_counter {"\\[(\\d+\\)]"};
  std::smatch match {};

  unsigned max_index = 0;

  while (std::regex_search(formula, match, index_counter))
    max_index = std::max(max_index, unsigned(std::stoi(match.str()) + 1));

  if (max_index > guesses.size()) {
    for (unsigned index = guesses.size(); index < max_index; index++)
      guesses.emplace_back(std::to_string(index), 0);
  }
  else
    guesses.resize(max_index);

}
