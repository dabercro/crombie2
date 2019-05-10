#include <crombie2/FlatUncertainty.h>
#include <crombie2/Misc.h>


using namespace crombie2;


FlatUncertainty::FlatUncertainty (const FlatUncertainty& other) :
  FlatUncertainty()
{

  copy(other);

}


namespace {

  bool check (const std::string& val, const GuiConfigurable& tocheck) {

    auto check_str = tocheck.get();
    if (not check_str.size())
      return true;

    auto vals = Misc::split(check_str, ",");
    for (auto& ele : vals) {
      if (ele == val)
        return true;
    }

    return false;

  }

}


bool FlatUncertainty::has_process (const std::string& proc) const {

  return check(proc, procs);

}


bool FlatUncertainty::has_region (const std::string& region) const {

  return check(region, regions);

}
