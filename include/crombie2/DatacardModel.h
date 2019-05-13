#ifndef CROMBIE2_DATACARDMODEL_H
#define CROMBIE2_DATACARDMODEL_H


#include <crombie2/CutModel.h>
#include <crombie2/FlatUncertainty.h>
#include <crombie2/PlotModel.h>
#include <crombie2/RateParams.h>
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

    RemoveList<RateParams> rateparams {};

    bool is_valid (const CutModel& cuts, const PlotModel& plots, bool batch = false) const;

    /**
       Get the RateParams that covers a given process.

       @returns A pointer to the needed RateParams.
                If there is none that cover the desired process,
                a null pointer is returned.
    */
    const RateParams* get_rateparams (const std::string& proc) const;

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  };

}


#endif
