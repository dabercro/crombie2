#include <iostream>

#include <crombie2/JSONAnalyzerMaster.h>


using namespace crombie2;


JSONAnalyzerMaster::JSONAnalyzerMaster (bool dojson, std::vector<Job>& jobs, const JSONModel& model) {

  if (dojson) {
    for (auto& job : jobs) {
      if (job.get_group().type == FileGroup::FileType::DATA)
        job.add_analyzer(&analyzers.emplace_back(model));
    }
  }

}


void JSONAnalyzerMaster::output () {

  LumiSelection output {};
  for (auto& analyzer : analyzers)
    output.add(analyzer.get_result());

  std::cout << output.show() << std::endl;

}
