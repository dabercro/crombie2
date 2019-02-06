#ifndef CROMBIE2_JSONANALYZER_H
#define CROMBIE2_JSONANALYZER_H


#include <crombie2/Analyzer.h>
#include <crombie2/JSONModel.h>
#include <crombie2/JSONRefs.h>
#include <crombie2/LumiSelection.h>


namespace crombie2 {
  class JSONAnalyzer : public Analyzer {
  public:
    JSONAnalyzer (const JSONModel& model);

    void make_requests (Tree& tree) override;

    void notify () override;

    const LumiSelection& get_result () const;

  private:
    const JSONModel& model;
    LumiSelection result {};
    std::unique_ptr<JSONRefs> ref {};

  };
}


#endif
