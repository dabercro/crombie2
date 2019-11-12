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


bool JSONModel::is_valid (Tree& tree) const {

  return tree.is_valid(runnum) and tree.is_valid(luminum);

}
