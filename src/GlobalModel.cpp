#include <crombie2/FileSystem.h>
#include <crombie2/GlobalModel.h>
#include <crombie2/Misc.h>


using namespace crombie2;


GlobalModel::GlobalModel () :
  SimpleModel {
    &inputdir,
    &nthreads,
    &tree,
    &luminosity,
    &normhist,
    &brancheslist
  } {}


GlobalModel::GlobalModel (const GlobalModel& other) :
  GlobalModel ()
{

  copy(other);

}


std::string GlobalModel::get_name () const {

  return "globals";

}


bool GlobalModel::is_valid () const {

  auto valid = FileSystem::exists(inputdir);

  if (not valid)
    Misc::message(get_name(), inputdir.get() + " does not exist");

  return valid;

}
