#ifndef CROMBIE2_REWEIGHTMODEL_H
#define CROMBIE2_REWEIGHTMODEL_H


#include <crombie2/Configurable.h>
#include <crombie2/SimpleModel.h>


namespace crombie2 {
  /**
     @brief A SimpleModel holding information for making Reweight plots
  */
  class ReweightModel : public SimpleModel {
  public:
    ReweightModel ();
    ReweightModel (const ReweightModel& other);

    std::string get_name () const override;

    /**
       @brief Which plot to use.

       If there is only one plot in the PlotModel,
       then this can be left blank.
    */
    Configurable<std::string> plotname {"Plot Name", ""};

    /// The legend entry of the histogram that should be matched
    Configurable<std::string> candle {"Candle", "Data"};

    /**
       @brief The legend of the histogram to scale

       If blank, then scale the total of all
       non-candle histograms to match the candle.
    */
    Configurable<std::string> signal {"Signal", ""};

    /// Location of the output file
    Configurable<std::string> output {"Output File", ""};

  };

}


#endif
