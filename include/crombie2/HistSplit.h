#ifndef CROMBIE2_HISTSPLIT_H
#define CROMBIE2_HISTSPLIT_H


#include <crombie2/Hist.h>


namespace crombie2 {
  class HistSplit {
  public:
    explicit HistSplit(const std::vector<std::string>& entries);

    void add (const std::vector<Hist>& adding);

    void scale (double lumi, double xs);

    /// First part of each element is the legend entry
    std::vector<std::pair<std::string, Hist>>& get_hists ();

  private:
    std::vector<std::pair<std::string, Hist>> hists {};

  };
}


#endif
