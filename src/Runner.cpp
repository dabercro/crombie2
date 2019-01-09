#include <chrono>
#include <mutex>
#include <thread>

#include <crombie2/HistAnalyzerMaster.h>
#include <crombie2/Runner.h>


using namespace crombie2;


Runner::Runner (unsigned num_files,
                const CutModel& cutmodel,
                const FileModel& filemodel,
                const GlobalModel& globalmodel,
                const PlotModel& plotmodel,
                Progress& progress) :
  num_files {num_files},
  cutmodel {cutmodel},
  filemodel {filemodel},
  globalmodel {globalmodel},
  plotmodel {plotmodel},
  progress {progress}
{

  jobs.reserve (num_files);

}


void Runner::run (const std::string& histoutputdir) {

  auto start = std::chrono::steady_clock::now();

  // Create all of the jobs

  for (auto& group : filemodel.filegroups) {
    for (auto& entry : group.files) {
      for (auto& name : entry.files(globalmodel)) {
        queue.emplace(jobs.emplace_back(globalmodel, group,
                                        entry, name));
      }
    }
  }

  // Create histograms
  HistAnalyzerMaster histanalyzers {histoutputdir, jobs, plotmodel, cutmodel, globalmodel};

  // Run jobs
  unsigned nthreads {globalmodel.nthreads};
  std::vector<std::thread> threads {};
  threads.reserve(nthreads);

  for (unsigned i_thread = 0; i_thread < nthreads; ++i_thread)
    threads.emplace_back([this] () { run_thread(); });

  for (auto& thread : threads)
    thread.join();

  progress.set_progress("Processing Output", 1.0);

  // Output histograms stuff
  histanalyzers.output();

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end - start;

  progress.set_progress(std::string("Finished in ") + std::to_string(diff.count()) + " s", 1.0);

}


namespace {

  std::mutex job_lock {};

}


void Runner::run_thread () {

  Job* job {nullptr};

  while (true) {

    job_lock.lock();

    if (queue.empty()) {
      job_lock.unlock();
      break;
    }

    job = queue.top().job;
    progress.set_progress(job->get_file_name(), double(done++)/num_files);
    queue.pop();

    job_lock.unlock();

    job->run();

  }

}
