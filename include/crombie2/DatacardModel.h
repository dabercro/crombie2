#ifndef CROMBIE2_DATACARDMODEL_H
#define CROMBIE2_DATACARDMODEL_H


#include <crombie2/CutModel.h>
#include <crombie2/FlatUncertainty.h>
#include <crombie2/PlotModel.h>
#include <crombie2/SelectionPlot.h>


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

    RemoveList<FlatUncertainty> flats {};

    bool is_valid (const CutModel& cuts, const PlotModel& plots, bool batch = false) const;

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  };

}


#endif
