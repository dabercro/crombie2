#include <exception>
#include <fstream>
#include <unordered_map>

#include <crombie2/FileSystem.h>
#include <crombie2/HistModel.h>


using namespace crombie2;


HistModel::HistModel (Job& job,
                      const GlobalModel& globalmodel,
                      const Plot& plot,
                      const std::string& var,
                      const std::string& cutstr,
                      const std::string& weightstr,
                      const OnTheFlyModel& reweight,
                      const EnvelopeModel& envelope) :
  inputdir {globalmodel.inputdir},
  inputfile {job.get_entry().name},
  nbins {plot.nbins},
  min {plot.min},
  max {plot.max},
  var {var},
  cutstr {cutstr},
  weightstr {weightstr},
  reweight {reweight},
  label {plot.label},
  analyzer_prototype {job, plot, var, cutstr, weightstr, globalmodel, reweight},
  no_stats{globalmodel.no_stats and job.get_group().type != FileGroup::FileType::DATA}

{

  for (auto& sub_proc : job.get_group().entries) {
    substrs.emplace_back(sub_proc.cut);
    legend_entries.emplace_back(sub_proc.legend);
  }

  bool is_mc = job.get_group().type != FileGroup::FileType::DATA;

  bool reweighing = reweight.list.size() and is_mc;

  // If data isn't saved, prepare the analyzers

  cache_file = reweighing ? "" : save() + ".dat";
  cached = FileSystem::exists(cache_file) and not reweighing;

  if (is_mc) {
    for (auto& env_type : envelope.list) {
      auto& model_list = envelope_models[env_type.name];
      for (auto& weight : env_type.get_cuts()) {
        if (weight.get().size())
          model_list.emplace_back(job, globalmodel, plot, var, cutstr,
                                  weightstr + " * " + weight.get(), reweight,
                                  EnvelopeModel()); // Need empty model to avoid recursion
      }
    }
  }

}


std::string HistModel::get_name () const {

  return "hist";

}


void HistModel::read (const Types::strings& config) {

  throw std::logic_error{"Class HistModel should not actually be read."};

}


std::list<std::string> HistModel::serialize () const {

  std::list<std::string> output {
    inputdir,
    inputfile,
    std::to_string(nbins),
    std::to_string(min),
    std::to_string(max),
    var,
    cutstr,
    weightstr
  };

  output.insert(output.end(), substrs.begin(), substrs.end());

  return output;

}


void HistModel::add_job (Job& job) {

  if (not cached)
    job.add_analyzer(&analyzers.emplace_back(analyzer_prototype));

  for (auto& [key, models] : envelope_models) {
    for (auto& hist : models)
      hist.add_job(job);
  }

}


HistSplit HistModel::get_histsplit () const {

  HistSplit output {legend_entries};

  static std::unordered_map<std::string, std::vector<Hist>> cached_hists {};

  if (cache_file.size()) {
    auto cached_hist = cached_hists.find(cache_file);

    if (cached_hist != cached_hists.end()) {
      output.add(cached_hist->second);
      return output;
    }
  }

  if (not cached) {
    // Merge analyzers
    for (auto& analyzer : analyzers)
      output.add(analyzer.get_result());

    // Dump the cache
    if (cache_file.size()) {

      std::ofstream file {cache_file};

      for (auto& hist_pair : output.get_hists()) {

        auto& hist = hist_pair.second;
        file << hist.get_total() << std::endl;
        auto& contents = hist.get_contents();
        auto& errors = hist.get_errors();
        for (unsigned i_bin = 0; i_bin < contents.size(); ++i_bin)
          file << contents.at(i_bin) << " " << errors.at(i_bin) << std::endl;

      }
    }
  }
  else {
    std::vector<Hist> hists {};

    std::ifstream file {cache_file};

    for (unsigned i_hist = 0; i_hist < substrs.size(); ++i_hist) {

      double total {};

      std::vector<double> contents {};
      std::vector<double> sumw2 {};

      file >> total;

      for (unsigned i_bin = 0; i_bin < nbins + 2; ++i_bin) {
        double bin_content {};
        double bin_w2 {};

        file >> bin_content >> bin_w2;

        contents.push_back(bin_content);
        sumw2.push_back(bin_w2);
      }

      hists.emplace_back(label, nbins, min, max, total).
        set_contents(contents, sumw2);

    }

    output.add(hists);

  }

  if (cache_file.size()) {
    std::vector<Hist> hists {};

    for (auto& hist : output.get_hists())
      hists.emplace_back(hist.second);

    cached_hists.insert({cache_file, std::move(hists)});
  }

  return output;

}


HistSplit HistModel::get_histsplit_with_env () const {

  auto output = get_histsplit();

  if (no_stats) {
    for (auto& split : output.get_hists())
      split.second.set_contents(split.second.get_contents(),
                                std::vector<double>(nbins + 2));
  }

  for (auto& [key, list] : envelope_models) {

    for (auto& histmodel : list) {

      auto env_split = histmodel.get_histsplit();

      for (unsigned i_split = 0; i_split < output.get_hists().size(); i_split++) {
        auto& outhist = output[i_split];
        outhist.add_env(key, env_split[i_split]);
      }
    }

  }

  return output;

}
