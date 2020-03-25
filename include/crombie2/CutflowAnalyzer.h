#ifndef CROMBIE2_CUTFLOWANALYZER_H
#define CROMBIE2_CUTFLOWANALYZER_H


#include <crombie2/Analyzer.h>
#include <crombie2/CutflowRefs.h>


namespace crombie2 {
  class CutflowAnalyzer : public Analyzer {
  public:
    CutflowAnalyzer (const Types::strings& cutflow, const std::string& weight = "1");

    void make_requests (Tree& tree) override;

    void notify () override;

    const std::vector<double>& get_result () const;

  private:
    Types::strings cuts;
    const std::string weight;
    std::vector<double> result;
    std::vector<CutflowRefs> refs {};

  };
}


#endif
