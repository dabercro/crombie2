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
