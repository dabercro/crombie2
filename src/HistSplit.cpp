#include <exception>

#include <crombie2/HistSplit.h>


using namespace crombie2;


HistSplit::HistSplit (const std::vector<std::string>& entries)
{

  hists.reserve(entries.size());
  for (auto& entry : entries)
    hists.emplace_back(entry, Hist());

}


void HistSplit::add (const std::vector<Hist>& adding) {

  if (hists.size() != adding.size())
    throw std::logic_error("Hist vectors don't match in size. Should be for same file.");

  for (unsigned i_hist = 0; i_hist < hists.size(); i_hist++)
    hists[i_hist].second.add(adding.at(i_hist));

}


void HistSplit::scale (double lumi, double xs) {

  for (auto& hist : hists)
    hist.second.scale(lumi, xs);

}


std::vector<std::pair<std::string, Hist>>& HistSplit::get_hists () {

  return hists;

}
