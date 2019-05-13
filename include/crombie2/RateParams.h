#ifndef CROMBIE2_RATEPARAMS_H
#define CROMBIE2_RATEPARAMS_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>


namespace crombie2 {
  class RateParams : public ConfigTable {
  public:
    RateParams () : ConfigTable {
      {&procs, &min, &max},
      true
    } {}
    RateParams (const RateParams& other);
    virtual ~RateParams () = default;

    Configurable<std::string> procs {"Processes", ""};
    Configurable<double> min {"Min", 0.2};
    Configurable<double> max {"Max", 5};

    bool has_process (const std::string& proc) const;

  };
}


#endif
