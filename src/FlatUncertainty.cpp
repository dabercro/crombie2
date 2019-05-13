#include <crombie2/FlatUncertainty.h>
#include <crombie2/Misc.h>


using namespace crombie2;


FlatUncertainty::FlatUncertainty (const FlatUncertainty& other) :
  FlatUncertainty()
{

  copy(other);

}


bool FlatUncertainty::has_process (const std::string& proc) const {

  return Misc::check_comma_field(proc, procs.get());

}


bool FlatUncertainty::has_region (const std::string& region) const {

  return Misc::check_comma_field(region, regions.get());

}
