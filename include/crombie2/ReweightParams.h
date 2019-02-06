#ifndef CROMBIE2_REWEIGHTPARAMS_H
#define CROMBIE2_REWEIGHTPARAMS_H

#include <crombie2/ReweightParams.h>


namespace crombie2 {
  class ReweightParams {
  public:
    bool doreweight;
    std::string selection;
    std::string plotname;
    std::string signal;
    std::string output;
  };
}


#endif
