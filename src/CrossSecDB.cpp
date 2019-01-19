#include <sstream>

#include <crombie2/CrossSecDB.h>
#include <crombie2/Misc.h>


using namespace crombie2;


CrossSecDB::CrossSecDB () :
  SimpleModel {&executable} {}


std::string CrossSecDB::get_name () const {

  return "crosssecdb";

}


double CrossSecDB::get_xs (const std::string& dataset) {

  double output {0};

  auto exe = executable.get();

  if (exe.size()) {
    std::stringstream converter {};
    converter << Misc::shell(exe + " " + dataset);
    converter >> output;
  }

  return output;

}
