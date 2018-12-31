#include <crombie2/CutString.h>


using namespace crombie2;


CutString::CutString (const std::string& name, const std::string& joiner) :
  name {"Name", name}, joiner {"Join With", joiner}, cuts {} {}


Cut& CutString::add_cut () {

  cuts.emplace_back("");
  return cuts.back();

}


std::list<Cut>& CutString::get_cuts () {

  return cuts;

}


const std::list<Cut>& CutString::get_cuts () const {

  return cuts;

}
