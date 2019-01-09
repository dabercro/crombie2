#ifndef CROMBIE2_HISTMODEL_H
#define CROMBIE2_HISTMODEL_H


#include <crombie2/HistAnalyzer.h>
#include <crombie2/HistSplit.h>


namespace crombie2 {
  class HistModel : public ConfigModel {
  public:
    HistModel (Job& job, const GlobalModel& globalmodel,
               const Plot& plot, const CutModel& cutmodel, const Selection& selection);

    std::string get_name () const override;

    HistSplit get_histsplit () const;

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

    const HistAnalyzer analyzer_prototype;     ///< All other analyzers will just be copied from this

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

    // Not saved in cache, but annoyingly still used at the moment
    std::string label;
    std::vector<std::string> legend_entries {};

  };
}


#endif
