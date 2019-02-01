#include <crombie2/GlobalModel.h>


using namespace crombie2;


GlobalModel::GlobalModel () :
  SimpleModel {
    &inputdir,
    &nthreads,
    &tree,
    &luminosity,
    &normhist
  } {}


GlobalModel::GlobalModel (const GlobalModel& other) :
  GlobalModel ()
{

  copy(other);

}


std::string GlobalModel::get_name () const {

  return "globals";

}
