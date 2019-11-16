#include <crombie2/CutString.h>


using namespace crombie2;


CutString::CutString (const std::string& name, const std::string& joiner) :
  Cuts(name), joiner {joiner} {}
