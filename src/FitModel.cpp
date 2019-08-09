#include <crombie2/FitModel.h>
#include <crombie2/Misc.h>


using namespace crombie2;


std::string FitModel::get_name () const {
  return "fits";
}


void FitModel::read (const Types::strings& config) {

  fits.clear();

  for (auto& line : config) {

    auto split = Misc::split(line, "; ");

    auto& fit = fits.append(split.front());

    if (split.size() == 2) {
      unsigned index = 0;
      for (auto& guess : Misc::tokenize(split.back()))
        fit.guesses[index++].set(guess);
    }

  }

}


std::list<std::string> FitModel::serialize () const {

  std::list<std::string> output {};

  for (auto& fit : fits) {
    auto& line = output.emplace_back(fit.get());

    if (fit.guesses.size())
      line += "; ";

    for (auto& guess : fit.guesses)
      line += guess.get() + " ";
  }

  return output;

}
