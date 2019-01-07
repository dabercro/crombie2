#include <unistd.h>

#include <gtkmm/progressbar.h>

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
  plotcontrol {plotpage, plotmodel},
  jobpage {jobpage}
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

  run();

}


void MainController::run() {

  auto num_files = filemodel.num_files(globalmodel);

  if (not num_files)
    return;

  Gtk::ProgressBar progress {};

  jobpage.box().pack_start (progress);
  progress.show();
  progress.set_text("Setting up");

  std::vector<Job> jobs;
  jobs.reserve(num_files);

  // Create all of the jobs

  for (auto& group : filemodel.filegroups) {
    for (auto& entry : group.files) {
      for (auto& name : entry.files(globalmodel)) {
        jobs.emplace_back(globalmodel, group, entry, name);
      }
    }
  }

  // Create histograms
  HistAnalyzerMaster histanalyzers {jobs, plotmodel, cutmodel};

  // Run jobs
  double done {0};

  for (auto& job : jobs) {
    progress.set_fraction(done/num_files);
    progress.set_text(job.get_file_name());
    done += 1;
    usleep(100000);
  }

  // Output histograms stuff
  histanalyzers.output(globalmodel);

}
