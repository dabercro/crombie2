#include <crombie2/HistAnalyzerMaster.h>
#include <crombie2/Job.h>
#include <crombie2/Runner.h>


using namespace crombie2;


Runner::Runner (unsigned num_files,
                const CutModel& cutmodel,
                const FileModel& filemodel,
                const GlobalModel& globalmodel,
                const PlotModel& plotmodel,
                Gtk::ProgressBar& progress) :
  num_files {num_files},
  cutmodel {cutmodel},
  filemodel {filemodel},
  globalmodel {globalmodel},
  plotmodel {plotmodel},
  progress {progress} {}



void Runner::run() {

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
  }

  // Output histograms stuff
  histanalyzers.output(globalmodel);

}
