#include <crombie2/PlotStyleModel.h>


using namespace crombie2;


PlotStyleModel::PlotStyleModel () :
  SimpleModel {
    &outplotdir,
    &plottype,
    &minratio,
    &maxratio,
    &ratiolabel,
    &normalize
  } {}


PlotStyleModel::PlotStyleModel (const PlotStyleModel& other) :
  PlotStyleModel ()
{

  copy(other);

}


std::string PlotStyleModel::get_name () const {

  return "plotstyle";

}
