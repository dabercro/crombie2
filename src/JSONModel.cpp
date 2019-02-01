#include <crombie2/JSONModel.h>


using namespace crombie2;


JSONModel::JSONModel () :
  SimpleModel {
    &runnum,
    &luminum
  } {}


JSONModel::JSONModel (const JSONModel& other) :
  JSONModel ()
{

  copy(other);

}


std::string JSONModel::get_name () const {

  return "json";

}
