#ifndef CROMBIE2_HISTANALYZER_H
#define CROMBIE2_HISTANALYZER_H


#include <crombie2/CutModel.h>
#include <crombie2/Job.h>
#include <crombie2/Hist.h>
#include <crombie2/HistRefs.h>
#include <crombie2/Plot.h>


namespace crombie2 {
  class HistAnalyzer : public Analyzer {
  public:
    HistAnalyzer (const Job& job, const Plot& plot, const Selection& selection, const CutModel& cutmodel);

    void make_requests (Tree& tree) override;

    void notify () override;

    std::vector<Hist>& get_result ();

    const Job& job;
    const Plot& plot;
    const Selection& selection;

  private:

    const std::string cutstr;
    const std::string weightstr;
    std::vector<std::string> substrs {};

    std::list<HistRefs> refs {};

    std::vector<Hist> hists {};
  };
}


#endif
