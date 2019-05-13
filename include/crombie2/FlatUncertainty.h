#ifndef CROMBIE2_FLATUNCERTAINTY_H
#define CROMBIE2_FLATUNCERTAINTY_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>


namespace crombie2 {
  class FlatUncertainty : public ConfigTable {
  public:
    FlatUncertainty () : ConfigTable {
      {&name, &shape, &value, &regions, &procs},
      true
    } {}
    FlatUncertainty (const FlatUncertainty& other);
    virtual ~FlatUncertainty () = default;

    Configurable<std::string> name {"Name", ""};
    Configurable<std::string> shape {"Shape", "lnN"};
    Configurable<double> value {"Value", 0};

    Configurable<std::string> regions {"Regions", "", "Comma-separated list"};
    Configurable<std::string> procs {"Processes", "", "Comma-separated list"};

    bool has_process (const std::string& proc) const;
    bool has_region (const std::string& region) const;

  };
}


#endif
