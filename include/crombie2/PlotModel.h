#ifndef CROMBIE2_PLOTMODEL_H
#define CROMBIE2_PLOTMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/Plot.h>


namespace crombie2 {
  /**
     @brief The ConfigModel that handles a list of plots to make
  */
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
