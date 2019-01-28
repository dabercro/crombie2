#include <crombie2/HistAnalyzer.h>
#include <crombie2/Misc.h>


using namespace crombie2;


HistAnalyzer::HistAnalyzer (const Job& job, const Plot& plot,
                            const std::string& var,
                            const std::string& cutstr,
                            const std::string& weightstr,
                            const GlobalModel& globalmodel) :
  plot {plot},
  var {var},
  cutstr {cutstr},
  weightstr {weightstr},
  total_str {globalmodel.normhist}
{

  auto& subs = job.get_group().entries;
  hists.reserve(subs.size());

  for (auto& entry : subs) {
    substrs.emplace_back(entry.cut);
    hists.emplace_back(plot.label, plot.nbins, plot.min, plot.max);
  }

}


void HistAnalyzer::make_requests (Tree& tree) {

  auto total = tree.get<TH1>(total_str)->GetBinContent(1);

  for (auto& hist : hists)
    hist.set_total(total);

  for (auto& substr : substrs)
    refs.emplace_back(tree.request(cutstr),
                      tree.request(var),
                      tree.request(weightstr),
                      tree.request(substr));

}


void HistAnalyzer::notify () {

  if (refs.front().cut) {

    unsigned i_hist {0};

    for (auto& ref : refs) {
      if (ref.sub) {
        hists[i_hist].fill(ref.expr, ref.weight);
        break;
      }
      ++i_hist;
    }
  }

}


const std::vector<Hist>& HistAnalyzer::get_result () const {

  return hists;

}
