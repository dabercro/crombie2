#ifndef CROMBIE2_SELECTION_H
#define CROMBIE2_SELECTION_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>


namespace crombie2 {

  class Selection {
  public:
    Selection (const std::string& cut, const std::string& data, const std::string& mc);
    Configurable<std::string> cut;
    Configurable<std::string> data_weight;
    Configurable<std::string> mc_weight;
    ConfigTable table {
      &cut, &data_weight, &mc_weight
    };
  };

}


#endif
