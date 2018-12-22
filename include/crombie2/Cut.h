#ifndef CROMBIE2_CUT_H
#define CROMBIE2_CUT_H

#include <string>

#include "crombie2/Configurable.h"

namespace crombie2 {

  /**
     A Cut is just a configurable string with a default relabel,
     which is based on the LHS of the cut.
  */
  class Cut : public Configurable<std::string> {
  public:
    Cut(const std::string& cut);
  };

}

#endif
