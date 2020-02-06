#include <crombie2/HistAnalyzer.h>
#include <crombie2/Misc.h>


using namespace crombie2;


HistAnalyzer::HistAnalyzer (const Job& job, const Plot& plot,
                            const std::string& var,
                            const std::string& cutstr,
                            const std::string& weightstr,
                            const GlobalModel& globalmodel,
                            const OnTheFlyModel& reweight) :
  type {job.get_group().type},
  plot {plot},
  reweight {reweight},
  var {var},
  cutstr {cutstr},
  weightstr {weightstr},
  total_str {globalmodel.normhist}
{

  auto& subs = job.get_group().entries;
  hists.reserve(subs.size());

  for (auto& entry : subs) {
    substrs.emplace_back(entry.cut);
    hists.emplace_back(plot.title, plot.label, plot.nbins, plot.min, plot.max);
  }

}



void HistAnalyzer::make_requests (Tree& tree) {

  auto total = get_total(tree);

  for (auto& hist : hists)
    hist.set_total(total);

  for (auto& substr : substrs)
    refs.emplace_back(tree.request(cutstr),
                      tree.request(var),
                      tree.request(weightstr),
                      tree.request(substr));

  if (type != FileGroup::FileType::DATA) {
    reweighters.reserve(reweight.list.size());

    for (auto& config : reweight.list)
      reweighters.emplace_back(config, tree);
  }

}


void HistAnalyzer::notify () {

  if (refs.front().cut) {

    unsigned i_hist {0};

    for (auto& ref : refs) {
      if (ref.sub) {

        double newweight {1.0};
        for (auto& reweigher : reweighters)
          newweight *= reweigher.eval();

        hists[i_hist].fill(ref.expr, ref.weight * newweight);
        break;

      }
      ++i_hist;
    }
  }

}


const std::vector<Hist>& HistAnalyzer::get_result () const {

  return hists;

}


double HistAnalyzer::get_total(Tree& tree) const {

  auto tokens = Misc::tokenize(total_str);

  if (tokens.front() == "BRANCH" and tokens.size() == 3) {

    // If data, we won't find what we're looking for, and we don't care
    if (type == FileGroup::FileType::DATA)
      return 0;

    auto* total_tree = tree.get<TTree>(tokens[1]);

    Float16_t output = 0; // Xbb setup, apparently

    total_tree->SetBranchAddress(tokens[2].data(), &output);

    total_tree->GetEntry(0);

    return output;
  }

  // Otherwise, we're looking at a histogram
  return tree.get<TH1>(total_str)->GetBinContent(1);

}
