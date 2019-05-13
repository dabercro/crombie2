#include <iostream>

#include <algorithm>
#include <regex>

#include <crombie2/FitConfig.h>


using namespace crombie2;


FitConfig::FitConfig (const std::string& expr) :
  Configurable<std::string>("Fit Expression", expr)
{

  // Hacky way to make sure the entry is filled
  resize_guesses();

}


void FitConfig::resize_guesses () {

  const std::string formula = get();

  std::regex index_counter {"\\[(\\d+)\\]"};

  unsigned max_index = 0;

  for (auto match = std::sregex_iterator(formula.begin(), formula.end(), index_counter);
       match != std::sregex_iterator(); ++match)
    max_index = std::max(max_index, unsigned(std::stoi((*match)[1].str()) + 1));

  if (max_index > guesses.size()) {
    for (unsigned index = guesses.size(); index < max_index; index++)
      guesses.emplace_back(std::to_string(index), 0);
  }
  else
    guesses.resize(max_index);

}