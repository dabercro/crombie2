#ifndef CROMBIE2_CUTFLOWANALYZER_H
#define CROMBIE2_CUTFLOWANALYZER_H


#include <crombie2/Analyzer.h>
#include <crombie2/CutflowRefs.h>


namespace crombie2 {
  class CutflowAnalyzer : public Analyzer {
  public:
    CutflowAnalyzer (const Types::strings& cutflow);

    void make_requests (Tree& tree) override;

    void notify () override;

    const std::vector<long>& get_result () const;

  private:
    Types::strings cuts;
    std::vector<long> result;
    std::vector<CutflowRefs> refs {};

  };
}


#endif
