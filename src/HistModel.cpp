#include <exception>
#include <fstream>

#include <crombie2/FileSystem.h>
#include <crombie2/HistModel.h>
#include <crombie2/Misc.h>


using namespace crombie2;


HistModel::HistModel (Job& job,
               const GlobalModel& globalmodel,
               const Plot& plot,
               const CutModel& cutmodel,
               const Selection& selection,
               const OnTheFlyModel& reweight) :
  inputdir {globalmodel.inputdir},
  inputfile {job.get_entry().name},
  nbins {plot.nbins},
  min {plot.min},
  max {plot.max},
  var {plot.expr(job.get_group().type)},
  cutstr {Misc::nminus1(var, cutmodel.expand(selection.cut))},
  weightstr {cutmodel.expand(job.get_group().type == FileGroup::FileType::DATA
                             ? selection.data_weight
                             : selection.mc_weight)},
  reweight {reweight},
  label {plot.label},
  analyzer_prototype {job, plot, var, cutstr, weightstr, globalmodel, reweight}

{

  for (auto& sub_proc : job.get_group().entries) {
    substrs.emplace_back(sub_proc.cut);
    legend_entries.emplace_back(sub_proc.legend);
  }

  bool reweighing = reweight.list.size();

  // If data isn't saved, prepare the analyzers

  cache_file = reweighing ? "" : save() + ".dat";
  cached = FileSystem::exists(cache_file) and not reweighing;

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

}


HistSplit HistModel::get_histsplit () const {

  HistSplit output {legend_entries};

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

  return output;

}
