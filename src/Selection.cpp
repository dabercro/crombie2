#include <crombie2/Selection.h>


using namespace crombie2;


Selection::Selection (const std::string& cut,
                      const std::string& data,
                      const std::string& mc,
                      const std::string& name) :
  cut {"Cut", cut},
  data_weight {"Data Weight", data},
  mc_weight {"MC Weight", mc},
  name {"Name", name} {}


Selection::Selection (const Selection& other) :
  cut {other.cut},
  data_weight {other.data_weight},
  mc_weight {other.mc_weight},
  name {other.name} {}


std::string Selection::get_name () const {

  auto output = name.get();
  if (not output.size())
    output = cut;
  return output;

}
