#ifndef CROMBIE2_RUNNER_H
#define CROMBIE2_RUNNER_H


#include <gtkmm/progressbar.h>

#include <crombie2/CutModel.h>
#include <crombie2/FileModel.h>
#include <crombie2/PlotModel.h>


namespace crombie2 {
  class Runner {
  public:
    Runner (unsigned num_files,
            const CutModel& cutmodel,
            const FileModel& filemodel,
            const GlobalModel& globalmodel,
            const PlotModel& plotmodel,
            Gtk::ProgressBar& progress);

    void run();

  private:
    unsigned num_files;
    CutModel cutmodel;
    FileModel filemodel;
    GlobalModel globalmodel;
    PlotModel plotmodel;

    Gtk::ProgressBar& progress;

  };
}


#endif
