#ifndef CROMBIE2_JSONANALYZERMASTER_H
#define CROMBIE2_JSONANALYZERMASTER_H


#include <crombie2/JSONAnalyzer.h>
#include <crombie2/Job.h>


namespace crombie2 {
  class JSONAnalyzerMaster {
  public:
    JSONAnalyzerMaster (bool dojson, std::vector<Job>& jobs, const JSONModel& model);

    /// Prints the JSON to the terminal
    void output ();

  private:
    std::list<JSONAnalyzer> analyzers {};

  };
}


#endif
