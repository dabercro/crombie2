#ifndef CROMBIE2_HISTANALYZERMASTER_H
#define CROMBIE2_HISTANALYZERMASTER_H


#include <crombie2/HistAnalysis.h>
#include <crombie2/HistModel.h>
#include <crombie2/PlotModel.h>
#include <crombie2/PlotStyleModel.h>
#include <crombie2/ReweightModel.h>


namespace crombie2 {
  class HistAnalyzerMaster {
  public:
    HistAnalyzerMaster (bool dohists,
                        const std::string& outputdir,
                        std::vector<Job>& jobs,
                        const PlotModel& plotmodel,
                        const CutModel& cutmodel,
                        const ReweightModel& reweightmodel,
                        const GlobalModel& globalmodel,
                        const PlotStyleModel& plotstylemodel);

    HistAnalysis get_analysis_histograms (const std::string& selection) const;

    /// Outputs histograms into the plots directory if outputdir was set
    void output () const;

  private:
    /// Place to dump plots. Can be blank.
    const std::string outputdir;

    /// Maps the output file and input directory or file to a histogram result
    Types::map<Types::map<HistModel>> histmodels {};

    /// Maps the input file name to cross sections
    Types::map<double> xs {};
    const PlotModel& plotmodel;
    const CutModel& cutmodel;
    const ReweightModel& reweightmodel;
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
