#ifndef CROMBIE2_HISTANALYZERMASTER_H
#define CROMBIE2_HISTANALYZERMASTER_H


#include <crombie2/HistAnalysis.h>
#include <crombie2/HistModel.h>
#include <crombie2/PlotModel.h>
#include <crombie2/PlotStyleModel.h>


namespace crombie2 {
  class HistAnalyzerMaster {
  public:
    HistAnalyzerMaster (bool dohists,
                        const std::string& outputdir,
                        std::vector<Job>& jobs,
                        const PlotModel& plotmodel,
                        const CutModel& cutmodel,
                        const GlobalModel& globalmodel,
                        const PlotStyleModel& plotstylemodel);

    /**
       @brief Get a HistAnalysis object from a selection, plot specification, and signal selection

       Empty strings are treated as using the only value possible.
       If multiple values for the parameter would be possible, it is an error.

       @param selection Must be filled if more than one selection exists. Gets plots from this selection.
       @param plotname Must be filled if more than one plot exists. Gets the given plot.
       @param signal If filled, Use this legend entry as the signal for the plots. Others are background.
       @returns HistAnalysis object
    */
    HistAnalysis get_analysis_histograms (const std::string& selection,
                                          const std::string& plotname,
                                          const std::string& signal) const;

    /// Outputs histograms into the plots directory if outputdir was set
    void output () const;

  private:
    /// Place to dump plots. Can be blank.
    const std::string outputdir;

    /// Maps the output file and input directory or file to a histogram result
    Types::map<Types::map<HistModel>> histmodels {};

    /// Maps the input file name to cross sections
    Types::map<double> xs {};
    const GlobalModel& globalmodel;
    const PlotStyleModel& plotstylemodel;

    /// Maps the input file name to type
    Types::map<FileGroup::FileType> types {};

    /// Maps the legend entry to styles
    Types::map<short> styles {};

    /// Get the scaled (by cross section and luminosity) HistSplit
    HistSplit scaled_split (const std::pair<std::string, HistModel>& histentry) const;

    /// Does the sorting and drawing for each individual plot
    void draw_plot(const std::string& output,
                   Types::map<Hist>& data,
                   Types::map<Hist>& mc,
                   Types::map<Hist>& signal) const;

  };
}


#endif
