#include <chrono>
#include <mutex>
#include <thread>


#include <crombie2/CutflowAnalyzerMaster.h>
#include <crombie2/HistAnalyzerMaster.h>
#include <crombie2/JSONAnalyzerMaster.h>
#include <crombie2/Misc.h>
#include <crombie2/Progress.h>
#include <crombie2/Runner.h>


using namespace crombie2;


Runner::Runner (unsigned num_files,
                const AllModels& allmodels,
                Progress& progress) :
  num_files {num_files},
  allmodels {allmodels},
  progress {progress}
{

  jobs.reserve (num_files);

}


void Runner::run (const RunConfig& config) {

  auto start = std::chrono::steady_clock::now();

  // Create all of the jobs

  FileModel filemodel {allmodels.get<FileModel>()};
  GlobalModel globalmodel {allmodels.get<GlobalModel>()};
  CutModel cutmodel {allmodels.get<CutModel>()};
  JSONModel jsonmodel {allmodels.get<JSONModel>()};
  ReweightModel reweightmodel {allmodels.get<ReweightModel>()};
  PlotModel plotmodel {allmodels.get<PlotModel>()};
  OnTheFlyModel ontheflymodel {allmodels.get<OnTheFlyModel>()};
  PlotStyleModel plotstylemodel {allmodels.get<PlotStyleModel>()};
  DatacardModel datacardmodel {allmodels.get<DatacardModel>()};
  FitModel fitmodel {allmodels.get<FitModel>()};
  CompareModel comparemodel {allmodels.get<CompareModel>()};

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
    config.doreweight
      or config.dirs.at("plots").size()
      or config.dirs.at("datacards").size(),
    config.dirs.at("plots"), jobs,
    plotmodel, cutmodel,
    reweightmodel, globalmodel,
    plotstylemodel, datacardmodel,
    ontheflymodel,
    config.dofit, fitmodel,
    comparemodel
  };

  CutflowAnalyzerMaster cutflowanalyzers {
    config.docutflow, jobs, cutmodel
  };

  JSONAnalyzerMaster jsonanalyzers {
    config.dolumi, jobs, jsonmodel
  };

  // Run jobs
  unsigned nthreads {globalmodel.nthreads};
  std::vector<std::thread> threads {};
  threads.reserve(nthreads);

  for (unsigned i_thread = 0; i_thread < nthreads; ++i_thread)
    threads.emplace_back([this] () { run_thread(); });

  for (auto& thread : threads)
    thread.join();

  if (progress.aborted()) {
    progress.set_progress("Aborted");
    return;
  }

  progress.set_progress("Processing Output", 1.0);

  // Output histograms stuff
  histanalyzers.output();

  // Create datacards
  histanalyzers.dumpdatacard(config.dirs.at("datacards"), filemodel);

  if (config.docutflow)
    cutflowanalyzers.output();
  if (config.dolumi)
    jsonanalyzers.output();

  // Reweight stuff
  if (config.doreweight) {
    for (auto& selection : cutmodel.selections) {
      std::string cut = selection.cut;
      histanalyzers.get_analysis_histograms(cut).
        reweight(reweightmodel.normalize, reweightmodel.output, cut + "_reweight");
      allmodels.save(Misc::replace(reweightmodel.output, "\\.root", ".cnf"));
    }
  }

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

    if (progress.aborted()) {
      progress.set_progress("Aborting");
      break;
    }

    Job* job = queue.top().job;
    progress.set_progress(job->get_file_name(), double(done++)/num_files);
    queue.pop();

    job_lock.unlock();

    job->run();

  }

}
