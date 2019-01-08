#include <crombie2/HistAnalyzerMaster.h>
#include <crombie2/HistSplit.h>


using namespace crombie2;


HistAnalyzerMaster::HistAnalyzerMaster (const std::string& outputdir, std::vector<Job>& jobs,
                                        const PlotModel& plotmodel, const CutModel& cutmodel) :
  outputdir {outputdir}
{

  // If no output directory, we are not going to make hist analyzers
  if (not outputdir.size())
    return;

  histanalyzers.reserve(jobs.size() * plotmodel.plots.size() * cutmodel.selections.size());

  for (auto& job : jobs) {
    for (auto& plot : plotmodel.plots) {
      for (auto& selection : cutmodel.selections) {
        auto& analyzer = histanalyzers.emplace_back(job, plot, selection, cutmodel);
        job.add_analyzer(&analyzer);
      }
    }
  }

}

void HistAnalyzerMaster::output () {

  if (not outputdir.size())
    return;

  // Map to output file and to input file
  Types::map<Types::map<HistSplit>> hists;

  for (auto& analyzer : histanalyzers) {
    std::string output_file = "";
  }

}
