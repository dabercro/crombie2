#ifndef CROMBIE2_PLOT_H
#define CROMBIE2_PLOT_H


#include <crombie2/FileGroup.h>


namespace crombie2 {
  class Plot : public ConfigTable {
  public:
    Plot ();
    Plot (const Plot& other);
    virtual ~Plot () = default;

    Configurable<std::string> name {"Variable", ""};
    Configurable<unsigned> nbins {"Number of Bins", 20};
    Configurable<double> min {"X Min", 0};
    Configurable<double> max {"X Max", 100};
    Configurable<std::string> label {"X Label", "[GeV]"};
    Configurable<std::string> data_var {"Data Variable", ""};
    Configurable<std::string> mc_var {"MC Variable", ""};
    Configurable<std::string> lines {"Verticle Lines", ""};
    Configurable<std::string> title {"Plot Title", ""};

    std::string expr (FileGroup::FileType type) const;

    std::vector<double> vert_lines() const;

  };

}


#endif
