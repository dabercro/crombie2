#ifndef CROMBIE2_HISTANALYZERMASTER_H
#define CROMBIE2_HISTANALYZERMASTER_H


#include <crombie2/CutModel.h>
#include <crombie2/HistAnalyzer.h>
#include <crombie2/Job.h>
#include <crombie2/PlotModel.h>


namespace crombie2 {
  class HistAnalyzerMaster {
  public:
    HistAnalyzerMaster (std::vector<Job>& jobs,
                        const PlotModel& plotmodel,
                        const CutModel& cutmodel);

  private:
    std::vector<HistAnalyzer> histanalyzers {};

  };
}


#endif
