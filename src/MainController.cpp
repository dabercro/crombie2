#include <crombie2/HistAnalyzerMaster.h>
#include <crombie2/MainController.h>


using namespace crombie2;


MainController::MainController (ConfigPage& globalpage,
                                ConfigPage& filepage,
                                ConfigPage& plotpage,
                                ConfigPage& selectionpage,
                                ConfigPage& uncertaintypage,
                                ConfigPage& jobpage) :
  cutcontrol {selectionpage, cutmodel},
  filecontrol {filepage, filemodel},
  globalcontrol {globalpage, globalmodel},
  plotcontrol {plotpage, plotmodel}
{

  button.set_border_width(10);

  jobpage.pack_end(submitbox, Gtk::PACK_SHRINK);
  submitbox.pack_start(button, Gtk::PACK_SHRINK);
  button.signal_clicked().
    connect(sigc::mem_fun(*this, &MainController::on_submit_job));

  submitbox.show();
  button.show();

}


void MainController::on_submit_job () {

  std::vector<Job> jobs;
  jobs.reserve(filemodel.num_files());

  // Create all of the jobs

  for (auto& group : filemodel.filegroups) {
    for (auto& entry : group.files) {
      for (auto& name : entry.files()) {
        jobs.emplace_back(globalmodel, group, entry, name);
      }
    }
  }

  // Create histograms
  HistAnalyzerMaster histanalyzers {jobs, plotmodel, cutmodel};

}
