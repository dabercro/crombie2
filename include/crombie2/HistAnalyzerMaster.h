#ifndef CROMBIE2_HISTANALYZERMASTER_H
#define CROMBIE2_HISTANALYZERMASTER_H


#include <crombie2/CompareModel.h>
#include <crombie2/DatacardModel.h>
#include <crombie2/FileModel.h>
#include <crombie2/FitModel.h>
#include <crombie2/HistAnalysis.h>
#include <crombie2/HistModelsWithLines.h>
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
                        const PlotStyleModel& plotstylemodel,
                        const DatacardModel& datacardmodel,
                        const OnTheFlyModel& onthefly,
                        bool dofit,
                        const FitModel& fitmodel,
                        const CompareModel& comparemodel);

    HistAnalysis get_analysis_histograms (const std::string& selection) const;

    /// Outputs histograms into the plots directory if outputdir was set
    void output () const;

    /// Creates datacard
    void dumpdatacard (const std::string& datadir,
                       const FileModel& filemodel) const;

  private:
    /// Place to dump plots. Can be blank.
    const std::string outputdir;

    /// Maps the output file and input directory or file to a histogram result
    Types::map<HistModelsWithLines> histmodels {};

    /// Maps the input file name to cross sections
    Types::map<double> xs {};
    const PlotModel& plotmodel;
    const CutModel& cutmodel;
    const ReweightModel& reweightmodel;
    const GlobalModel& globalmodel;
    const PlotStyleModel& plotstylemodel;
    const DatacardModel& datacardmodel;
    bool dofit;
    const FitModel& fitmodel;
    const CompareModel& comparemodel;

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
                   Types::map<Hist>& signal,
                   bool blinding,
                   bool comparing,
                   std::vector<double> lines = {}) const;

  };
}


#endif
