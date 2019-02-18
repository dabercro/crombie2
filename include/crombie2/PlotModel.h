#ifndef CROMBIE2_PLOTMODEL_H
#define CROMBIE2_PLOTMODEL_H


#include <crombie2/ListModel.h>
#include <crombie2/Plot.h>


namespace crombie2 {
  /**
     @brief The ConfigModel that handles a list of plots to make
  */
  class PlotModel : public ListModel<Plot> {

  public:
    std::string get_name () const override;

  private:
    void read (const Types::strings& config) override;
    std::list<std::string> serialize () const override;

  };
}


#endif
