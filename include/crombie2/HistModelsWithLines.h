#ifndef CROMBIE2_HISTMODELSWITHLINES_H
#define CROMBIE2_HISTMODELSWITHLINES_H


#include <vector>

#include <crombie2/HistModel.h>
#include <crombie2/Types.h>


namespace crombie2 {

  class HistModelsWithLines : public Types::map<HistModel> {
  public:
    std::vector<double> lines {};
  };

}

#endif
