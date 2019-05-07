#include <crombie2/DatacardModel.h>


using namespace crombie2;


DatacardModel::DatacardModel () :
  SimpleModel {
    &outdir
  } {}


DatacardModel::DatacardModel (const DatacardModel& other) :
  DatacardModel ()
{

  copy(other);

}


std::string DatacardModel::get_name () const {

  return "datacard";

}
