#ifndef CROMBIE2_PLOTMODEL_H
#define CROMBIE2_PLOTMODEL_H


#include <crombie2/ListModel.h>
#include <crombie2/Tree.h>
#include <crombie2/Plot.h>


namespace crombie2 {
  /**
     @brief The ConfigModel that handles a list of plots to make
  */
  class PlotModel : public ListModel<Plot> {

  public:
    std::string get_name () const override;

    bool is_valid () const override;

    bool is_valid (bool print) const;
    bool is_valid (Tree& tree) const;

  private:
    void read (const Types::strings& config) override;
    std::list<std::string> serialize () const override;

  };
}


#endif
