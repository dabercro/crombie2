#include <crombie2/Misc.h>
#include <crombie2/ReweightModel.h>


using namespace crombie2;


ReweightModel::ReweightModel () :
  SimpleModel {
    &plotname,
    &candle,
    &signal,
    &output,
    &normalize
  } {}


ReweightModel::ReweightModel (const ReweightModel& other) :
  ReweightModel ()
{

  copy(other);

}


std::string ReweightModel::get_name () const {

  return "reweight";

}


bool ReweightModel::is_valid (const PlotModel& plots) const {

  for (auto& plot : plots.list) {
    if (plotname.get() == plot.name.get())
      return true;
  }

  Misc::message("Reweight model error",
                std::string("Could not find plot named \"")
                + plotname.get() + "\". Check the Plots page");

  return false;

}
