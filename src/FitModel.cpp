#include <crombie2/FitModel.h>


using namespace crombie2;


std::string FitModel::get_name () const {
  return "fits";
}


void FitModel::read (const Types::strings& config) {

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
