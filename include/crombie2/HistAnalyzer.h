#ifndef CROMBIE2_HISTANALYZER_H
#define CROMBIE2_HISTANALYZER_H


#include <crombie2/Analyzer.h>
#include <crombie2/Hist.h>
#include <crombie2/HistRefs.h>
#include <crombie2/LegendEntry.h>


namespace crombie2 {
  class HistAnalyzer : public Analyzer {
  public:
    HistAnalyzer (const std::string& cut, const std::string& expr,
                  const std::string& weight, const std::list<LegendEntry>& subs,
                  const std::string& label, unsigned numbins, double min, double max);

    void make_requests (Tree& tree) override;

    void notify () override;

    std::vector<Hist>& get_result ();

  private:
    const std::string cutstr;
    const std::string exprstr;
    const std::string weightstr;
    std::vector<const std::string> substrs {};

    std::list<HistRefs> refs {};

    std::vector<Hist> hists {};
  };
}


#endif
