#ifndef CROMBIE2_PLOTSTYLEMODEL_H
#define CROMBIE2_PLOTSTYLEMODEL_H


#include <crombie2/BoolConfigurable.h>
#include <crombie2/Configurable.h>
#include <crombie2/SimpleModel.h>


namespace crombie2 {
  /**
     @brief A SimpleModel holding information for styling plots
  */
  class PlotStyleModel : public SimpleModel {
  public:
    PlotStyleModel ();
    PlotStyleModel (const PlotStyleModel& other);

    std::string get_name () const override;

    /// The directory to output plots
    Configurable<std::string> outplotdir {"Plot Output", "plots"};

    /// The type to label the plot
    Configurable<std::string> plottype {"Plot Type", "Preliminary"};

    /// The smallest possible value for the ratio pad
    Configurable<double> minratio {"Ratio Minimum", 0.0};

    /// The largest possible value for the ratio pad
    Configurable<double> maxratio {"Ratio Maximum", 2.0};

    /// The ratio pad axis label
    Configurable<std::string> ratiolabel {"Ratio Label", "Data/Pred."};

    /// Determine if the plots are normalized or not
    BoolConfigurable normalize {"Normalize Plots"};

    Configurable<std::string> blind {"Blind Channel", ""};

    /// The buffer for the ratio pad
    Configurable<double> ratiobuffer {"Ratio Buffer", 0,
        "The size of the extra buffer in the ratio plot. Values between 0 and 1 make the most sense."};

    /// The forced maximum for the top pad
    BoolConfigurable forcetop {"Force top pad values"};

    /// The forced maximum for the top pad
    Configurable<double> maximum {"Maximum", 0,
        "The forced maximum for the top pad's y-value."};

    /// The forced minimum for the top pad
    Configurable<double> minimum {"Minimum", 0,
        "The forced minimum for the top pad's y-value."};

    BoolConfigurable saveroot {"Save .root file"};

    /// If checked, use the global luminosity
    BoolConfigurable usegloballumi {"Keep Global Luminosity"};

    /// If checked, use log scale for top pad
    BoolConfigurable logy {"Use Log Scale on Y-axis"};

    BoolConfigurable donminus1 {"Do N-1 Plots", true};

  };

}


#endif
