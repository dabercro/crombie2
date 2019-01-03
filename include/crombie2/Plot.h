#ifndef CROMBIE2_PLOT_H
#define CROMBIE2_PLOT_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>


namespace crombie2 {
  class Plot {
  public:
    Configurable<std::string> name {"Variable", ""};
    Configurable<unsigned> nbins {"Number of Bins", 20};
    Configurable<double> min {"X Min", 0};
    Configurable<double> max {"X Max", 100};
    Configurable<std::string> label {"X Label", "[GeV]"};
    Configurable<std::string> data_var {"Data Variable", ""};
    Configurable<std::string> mc_var {"MC Variable", ""};
    ConfigTable<> table {
      &name, &nbins, &min, &max, &label, &data_var, &mc_var
    };
  };

}


#endif
