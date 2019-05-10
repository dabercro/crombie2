#ifndef CROMBIE2_FLATUNCERTAINTY_H
#define CROMBIE2_FLATUNCERTAINTY_H


#include <crombie2/ConfigTable.h>


namespace crombie2 {
  class FlatUncertainty : public ConfigTable {
  public:
    FlatUncertainty () : ConfigTable {
      {&name, &shape, &value, &regions, &procs},
      true
    } {}
    FlatUncertainty (const FlatUncertainty& other) : FlatUncertainty() { copy(other); }
    virtual ~FlatUncertainty () = default;

    Configurable<std::string> name {"Name", ""};
    Configurable<std::string> shape {"Shape", "lnN"};
    Configurable<double> value {"Value", 0};

    Configurable<std::string> regions {"Regions", ""};
    Configurable<std::string> procs {"Processes", ""};

  };
}


#endif
