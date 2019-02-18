#include <crombie2/ReweightReader.h>


using namespace crombie2;


ReweightReader::ReweightReader (const ReweightReader& other) :
  expr {other.expr},
  cut {other.cut},
  file {other.file},
  hist {other.hist} {}
