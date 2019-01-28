#ifndef CROMBIE2_CUTFLOWANALYZERMASTER_H
#define CROMBIE2_CUTFLOWANALYZERMASTER_H


#include <crombie2/CutModel.h>
#include <crombie2/CutflowAnalyzer.h>
#include <crombie2/Job.h>


namespace crombie2 {
  class CutflowAnalyzerMaster {
  public:
    CutflowAnalyzerMaster (bool docutflow, std::vector<Job>& jobs, const CutModel& cutmodel);

    /// Prints the cutflow to the terminal
    void output ();

  private:
    CutModel model;
    /// Mapped by the selection label to a list of analyzers
    Types::map<std::list<CutflowAnalyzer>> analyzers {};

  };
}


#endif
