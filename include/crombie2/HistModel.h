#ifndef CROMBIE2_HISTMODEL_H
#define CROMBIE2_HISTMODEL_H


#include <crombie2/EnvelopeModel.h>
#include <crombie2/HistAnalyzer.h>
#include <crombie2/HistSplit.h>


namespace crombie2 {
  class HistModel : public ConfigModel {
  public:
    HistModel (Job& job,
               const GlobalModel& globalmodel,
               const Plot& plot,
               const std::string& var,
               const std::string& cutstr,
               const std::string& weightstr,
               const OnTheFlyModel& reweight,
               const EnvelopeModel& envelope);

    std::string get_name () const override;

    HistSplit get_histsplit () const;

    HistSplit get_histsplit_with_env () const;

    std::pair<HistSplit, HistSplit> get_min_max_env_hist (const std::string& envelope_name) const;

    void add_job (Job& job);

  protected:

    /**
       Always throws exception.
       This class is not actually for reading anything, just caching.
    */
    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  private:

    std::string cache_file {};
    bool cached {false};
    std::list<HistAnalyzer> analyzers {};      ///< Analyzers are only needed when the hist isn't already cached

    /// Map name of uncertainty to list of histograms to make envelope with
    std::map<std::string, std::list<HistModel>> envelope_models {};

    // Saved in cache

    // Input files
    const std::string inputdir;
    const std::string inputfile;

    // Plot
    const unsigned nbins;
    const double min;
    const double max;
    const std::string var;

    // Selection
    const std::string cutstr;
    const std::string weightstr;
    std::vector<std::string> substrs {};

    const OnTheFlyModel& reweight;

    // Not saved in cache, but annoyingly still used at the moment
    std::string label;
    std::vector<std::string> legend_entries {};

    const HistAnalyzer analyzer_prototype;     ///< All other analyzers will just be copied from this

    bool no_stats;

  };
}


#endif
