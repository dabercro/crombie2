#include <crombie2/HistAnalyzer.h>


using namespace crombie2;


HistAnalyzer::HistAnalyzer (const FileGroup& group, const Plot& plot, const Selection& selection) :
  cutstr {selection.cut},
  exprstr {plot.expr(group.type)},
  weightstr {group.type == FileGroup::FileType::DATA
      ? selection.data_weight
      : selection.mc_weight}
{

  auto& subs = group.entries;
  hists.reserve(subs.size());

  for (auto& entry : subs) {
    substrs.emplace_back(entry.cut);
    hists.emplace_back(plot.label, plot.nbins, plot.min, plot.max);
  }

}


void HistAnalyzer::make_requests (Tree& tree) {

  for (auto& substr : substrs)
    refs.emplace_back(tree.request(cutstr),
                      tree.request(exprstr),
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


std::vector<Hist>& HistAnalyzer::get_result () {

  return hists;

}
