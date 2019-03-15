#ifndef CROMBIE2_RUNNER_H
#define CROMBIE2_RUNNER_H


#include <queue>

#include <crombie2/CutModel.h>
#include <crombie2/FileModel.h>
#include <crombie2/JSONModel.h>
#include <crombie2/JobSorter.h>
#include <crombie2/OnTheFlyModel.h>
#include <crombie2/PlotModel.h>
#include <crombie2/Progress.h>
#include <crombie2/ReweightModel.h>


namespace crombie2 {

  /**
     @brief Copies models and runs jobs in a thread launched by the MainController
  */
  class Runner {
  public:
    Runner (unsigned num_files,
            const CutModel& cutmodel,
            const FileModel& filemodel,
            const GlobalModel& globalmodel,
            const JSONModel& jsonmodel,
            const ReweightModel& reweightmodel,
            const OnTheFlyModel& ontheflymodel,
            const PlotModel& plotmodel,
            const PlotStyleModel& plotstylemodel,
            Progress& progress);

    void run(const std::string& histoutputdir,
             bool docutflow, bool dolumi,
             bool doreweight, bool re_normalize);

  private:
    unsigned num_files;
    CutModel cutmodel;
    FileModel filemodel;
    GlobalModel globalmodel;
    JSONModel jsonmodel;
    ReweightModel reweightmodel;
    OnTheFlyModel ontheflymodel;
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
