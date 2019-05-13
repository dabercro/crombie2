#include <crombie2/RateParams.h>
#include <crombie2/Misc.h>


using namespace crombie2;


RateParams::RateParams (const RateParams& other) :
  RateParams()
{

  copy(other);

}


bool RateParams::has_process (const std::string& proc) const {

  return Misc::check_comma_field(proc, procs.get());

}
