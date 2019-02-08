#include <chrono>
#include <mutex>
#include <thread>

#include <crombie2/CutflowAnalyzerMaster.h>
#include <crombie2/HistAnalyzerMaster.h>
#include <crombie2/JSONAnalyzerMaster.h>
#include <crombie2/Runner.h>


using namespace crombie2;


Runner::Runner (unsigned num_files,
                const CutModel& cutmodel,
                const FileModel& filemodel,
                const GlobalModel& globalmodel,
                const JSONModel& jsonmodel,
                const ReweightModel& reweightmodel,
                const PlotModel& plotmodel,
                const PlotStyleModel& plotstylemodel,
                Progress& progress) :
  num_files {num_files},
  cutmodel {cutmodel},
  filemodel {filemodel},
  globalmodel {globalmodel},
  jsonmodel {jsonmodel},
  reweightmodel {reweightmodel},
  plotmodel {plotmodel},
  plotstylemodel {plotstylemodel},
  progress {progress}
{

  jobs.reserve (num_files);

}


void Runner::run (const std::string& histoutputdir,
                  bool docutflow, bool dolumi,
                  bool doreweight, bool re_normalize) {

  auto start = std::chrono::steady_clock::now();

  // Create all of the jobs

  for (auto& group : filemodel.filegroups) {
    for (auto& entry : group.files) {
      for (auto& name : entry.files(globalmodel.inputdir)) {
        queue.emplace(jobs.emplace_back(globalmodel, group,
                                        entry, name));
      }
    }
  }

  // Create histograms
  HistAnalyzerMaster histanalyzers {
    doreweight or histoutputdir.size(),
    histoutputdir, jobs,
    plotmodel, cutmodel,
    reweightmodel, globalmodel, plotstylemodel
  };

  CutflowAnalyzerMaster cutflowanalyzers {
    docutflow, jobs, cutmodel
  };

  JSONAnalyzerMaster jsonanalyzers {
    dolumi, jobs, jsonmodel
  };

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
  if (docutflow)
    cutflowanalyzers.output();
  if (dolumi)
    jsonanalyzers.output();

  // Reweight stuff
  if (doreweight)
    histanalyzers.get_analysis_histograms().
      reweight(re_normalize, reweightmodel.output);


  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end - start;

  progress.set_progress(std::string("Finished in ") + std::to_string(diff.count()) + " s", 1.0);

}


namespace {

  std::mutex job_lock {};

}


void Runner::run_thread () {

  while (true) {

    job_lock.lock();

    if (queue.empty()) {
      job_lock.unlock();
      break;
    }

    Job* job = queue.top().job;
    progress.set_progress(job->get_file_name(), double(done++)/num_files);
    queue.pop();

    job_lock.unlock();

    job->run();

  }

}
