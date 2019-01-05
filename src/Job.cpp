#include <crombie2/Job.h>


using namespace crombie2;


Job::Job (const GlobalModel& globalmodel, const std::string& file_name) :
  tree {file_name, globalmodel.tree.get()} {}


void Job::add_analyzer (Analyzer* analyzer) {

  analyzer->make_requests(tree);
  analyzers.push_back(analyzer);

}


void Job::run () {

  while (tree.next()) {
    for (auto* analyzer : analyzers)
      analyzer->notify();
  }

}
