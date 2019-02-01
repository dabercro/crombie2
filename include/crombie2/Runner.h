#ifndef CROMBIE2_RUNNER_H
#define CROMBIE2_RUNNER_H


#include <queue>

#include <crombie2/CutModel.h>
#include <crombie2/FileModel.h>
#include <crombie2/JSONModel.h>
#include <crombie2/JobSorter.h>
#include <crombie2/PlotModel.h>
#include <crombie2/Progress.h>


namespace crombie2 {

  class Runner {
  public:
    Runner (unsigned num_files,
            const CutModel& cutmodel,
            const FileModel& filemodel,
            const GlobalModel& globalmodel,
            const JSONModel& jsonmodel,
            const PlotModel& plotmodel,
            const PlotStyleModel& plotstylemodel,
            Progress& progress);

    void run(const std::string& histoutputdir,
             bool docutflow, bool dolumi);

  private:
    unsigned num_files;
    CutModel cutmodel;
    FileModel filemodel;
    GlobalModel globalmodel;
    JSONModel jsonmodel;
    PlotModel plotmodel;
    PlotStyleModel plotstylemodel;

    Progress& progress;

    std::vector<Job> jobs {};
    std::priority_queue<JobSorter> queue {};

    unsigned done {0};

    void run_thread ();

  };
}


#endif
