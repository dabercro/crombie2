#include <exception>

#include <crombie2/HistSplit.h>


namespace crombie2;


HistSplit::HistSplit(const FileGroup& group) {

  for (auto& entry : group.entries)
    hists.emplace_back();

}


void HistSplit::add (std::vector<Hist> adding) {

  if (hists.size() != adding.size())
    throw std::logic_error("Hist vectors don't match in size. Should be for same file.");

  for (unsigned i_hist = 0; i_hist < hists.size(); i_hist++)
    hists[i_hist].add(adding[i_hist]);

}


std::vector<Hist>& get_hists () {
  return hists;
}
