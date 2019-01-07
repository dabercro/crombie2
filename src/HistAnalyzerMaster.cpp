#include <crombie2/HistAnalyzerMaster.h>


using namespace crombie2;


HistAnalyzerMaster::HistAnalyzerMaster (std::vector<Job>& jobs, const PlotModel& plotmodel, const CutModel& cutmodel) {

  histanalyzers.reserve(jobs.size() * plotmodel.plots.size() * cutmodel.selections.size());

  for (auto& job : jobs) {
    const auto& group = job.get_group();
    for (auto& plot : plotmodel.plots) {
      for (auto& selection : cutmodel.selections)
        job.add_analyzer(&histanalyzers.emplace_back(group, plot, selection));
    }
  }

}
