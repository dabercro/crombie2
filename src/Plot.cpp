#include <crombie2/Plot.h>


using namespace crombie2;


Plot::Plot (const Plot& other) :
  name {other.name},
  nbins {other.nbins},
  min {other.min},
  max {other.max},
  label {other.label},
  data_var {other.data_var},
  mc_var {other.mc_var} {}


std::string Plot::expr (FileGroup::FileType type) const {

  auto& cand = type == FileGroup::FileType::DATA
    ? data_var
    : mc_var;

  return cand.get().size() ? cand.get() : name.get();

}
