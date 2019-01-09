#ifndef CROMBIE2_HISTANALYZERMASTER_H
#define CROMBIE2_HISTANALYZERMASTER_H


#include <crombie2/HistModel.h>
#include <crombie2/PlotModel.h>


namespace crombie2 {
  class HistAnalyzerMaster {
  public:
    HistAnalyzerMaster (const std::string& outputdir,
                        std::vector<Job>& jobs,
                        const PlotModel& plotmodel,
                        const CutModel& cutmodel,
                        const GlobalModel& globalmodel);

    void output ();

  private:
    const std::string outputdir;

    /// Maps the output file and input directory or file to a histogram result
    Types::map<Types::map<HistModel>> histmodels {};

    /// Maps the input file name to cross sections
    Types::map<double> xs {};
    const GlobalModel& globalmodel;

    /// Maps the input file name to type
    Types::map<FileGroup::FileType> types {};

    /// Maps the legend entry to styles
    Types::map<short> styles {};

    /// Does the sorting and drawing for each individual plot
    void draw_plot(const std::string& output,
                   Types::map<Hist>& data,
                   Types::map<Hist>& mc,
                   Types::map<Hist>& signal);

  };
}


#endif
