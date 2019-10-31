#include <crombie2/Misc.h>
#include <crombie2/Plot.h>


using namespace crombie2;


Plot::Plot (const Plot& other) :
  Plot()
{

  copy(other);

}


std::string Plot::expr (FileGroup::FileType type) const {

  auto& cand = type == FileGroup::FileType::DATA
    ? data_var
    : mc_var;

  return cand.get().size() ? cand.get() : name.get();

}


std::vector<double> Plot::vert_lines() const {

  std::vector <double> output {};

  for (auto& string : Misc::tokenize(lines))
    output.push_back(std::stod(string));

  return output;


}
