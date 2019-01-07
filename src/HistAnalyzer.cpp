#include <crombie2/HistAnalyzer.h>


using namespace crombie2;


HistAnalyzer::HistAnalyzer (const std::string& cut, const std::string& expr,
                            const std::string& weight, const std::list<LegendEntry>& subs,
                            const std::string& label, unsigned numbins, double min, double max) :
  cutstr {cut},
  exprstr {expr},
  weightstr {weight}
{

  hists.reserve(subs.size());

  for (auto& entry : subs) {
    substrs.emplace_back(entry.cut.get());
    hists.emplace_back(label, numbins, min, max);
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
