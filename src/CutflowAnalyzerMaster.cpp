#include <iomanip>
#include <iostream>

#include <crombie2/CutflowAnalyzerMaster.h>


using namespace crombie2;


CutflowAnalyzerMaster::CutflowAnalyzerMaster (bool docutflow, std::vector<Job>& jobs,
                                              const CutModel& cutmodel) :
  model {cutmodel}
{

  if (docutflow) {
    for (auto& selection : model.selections) {
      auto& label = selection.cut;
      auto cutflow = model.cutflow(label);
      for (auto& job : jobs) {
        if (job.get_group().type == FileGroup::FileType::DATA)
          job.add_analyzer(&analyzers[label].emplace_back(cutflow));
      }
    }
  }

}


void CutflowAnalyzerMaster::output () {

  for (auto& selection : analyzers) {
    auto& label = selection.first;
    std::cout << "-------------------" << std::endl
              << label << std::endl
              << "-------------------" << std::endl;

    auto cutflow = model.cutflow(label);
    std::vector<long> output (cutflow.size());

    for (auto& analyzer : selection.second) {
      unsigned index = 0;
      for (auto result : analyzer.get_result())
        output[index++] += result;
    }

    unsigned index = 0;
    for (auto& cut : cutflow)
      std::cout << std::setw(25) << cut
                << std::setw(15) << output[index++] << std::endl;

  }

}
