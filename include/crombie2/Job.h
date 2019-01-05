#ifndef CROMBIE2_JOB_H
#define CROMBIE2_JOB_H


#include <vector>

#include <crombie2/Analyzer.h>
#include <crombie2/GlobalModel.h>


namespace crombie2 {
  class Job {
  public:
    Job (const GlobalModel& globalmodel, const std::string& file_name);

    void add_analyzer (Analyzer* analyzer);
    void run ();

  private:

    std::vector<Analyzer*> analyzers;
    Tree tree;

  };
}


#endif
