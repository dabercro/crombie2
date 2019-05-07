#ifndef CROMBIE2_RUNNER_H
#define CROMBIE2_RUNNER_H


#include <queue>

#include <crombie2/AllModels.h>
#include <crombie2/JobSorter.h>
#include <crombie2/RunConfig.h>


namespace crombie2 {

  /**
     @brief Copies models and runs jobs in a thread launched by the MainController
  */
  class Runner {
  public:
    Runner (unsigned num_files,
            const AllModels& allmodels,
            Progress& progress);

    void run (const RunConfig& config);

  private:
    unsigned num_files;
    AllModels allmodels;
    Progress& progress;

    std::vector<Job> jobs {};
    std::priority_queue<JobSorter> queue {};

    unsigned done {0};

    void run_thread ();

  };
}


#endif
