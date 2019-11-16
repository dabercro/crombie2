#include <crombie2/Cuts.h>

using namespace crombie2;


Cuts::Cuts (const std::string& name) :
  name {"Name", name}, cuts {} {}


Cut& Cuts::add_cut () {

  cuts.append("");
  return cuts.back();

}


RemoveList<Cut>& Cuts::get_cuts () {

  return cuts;

}


const RemoveList<Cut>& Cuts::get_cuts () const {

  return cuts;

}
