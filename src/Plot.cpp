#include <crombie2/Plot.h>


using namespace crombie2;


std::string Plot::expr (FileGroup::FileType type) const {

  auto& cand = type == FileGroup::FileType::DATA
    ? data_var
    : mc_var;

  return cand.get().size() ? cand.get() : name.get();

}
