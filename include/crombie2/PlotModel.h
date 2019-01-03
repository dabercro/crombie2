#ifndef CROMBIE2_PLOTMODEL_H
#define CROMBIE2_PLOTMODEL_H


#include <crombie2/Plot.h>


namespace crombie2 {
  class PlotModel : public ConfigModel {
  public:

    std::string get_name () const override;

    Plot& add_plot ();

    std::list<Plot> plots {};

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  };
}


#endif
