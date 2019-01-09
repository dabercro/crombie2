#include <crombie2/HistAnalyzer.h>


using namespace crombie2;


HistAnalyzer::HistAnalyzer (const Job& job, const Plot& plot, const Selection& selection, const CutModel& cutmodel) :
  job {job},
  plot {plot},
  selection {selection},
  cutstr {cutmodel.expand(selection.cut)},
  weightstr {cutmodel.expand(job.get_group().type == FileGroup::FileType::DATA
                             ? selection.data_weight
                             : selection.mc_weight)}
{

  auto& subs = job.get_group().entries;
  hists.reserve(subs.size());

  for (auto& entry : subs) {
    substrs.emplace_back(entry.cut);
    hists.emplace_back(plot.label, plot.nbins, plot.min, plot.max);
  }

}


void HistAnalyzer::make_requests (Tree& tree) {

  for (auto& substr : substrs)
    refs.emplace_back(tree.request(cutstr),
                      tree.request(plot.expr(job.get_group().type)),
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


std::string HistAnalyzer::get_output_file () const {

  return selection.cut.get() + "_" + plot.name.get();

}


std::string HistAnalyzer::get_input_file () const {

  return job.get_entry().name.get();

}


const FileGroup& HistAnalyzer::get_group () const {

  return job.get_group();

}
