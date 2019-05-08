#ifndef CROMBIE2_DATACARDMODEL_H
#define CROMBIE2_DATACARDMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/Configurable.h>
#include <crombie2/SelectionPlot.h>
#include <crombie2/RemoveList.h>

namespace crombie2 {
  /**
     @brief A SimpleModel holding information for styling plots
  */
  class DatacardModel : public ConfigModel {

  public:

    std::string get_name () const override;

    /// The directory to output plots
    Configurable<std::string> outdir {"Datacard Output", "datacard"};

    RemoveList<SelectionPlot> hists {};

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  };

}


#endif
