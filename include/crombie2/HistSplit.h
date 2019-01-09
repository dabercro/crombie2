#ifndef CROMBIE2_HISTSPLIT_H
#define CROMBIE2_HISTSPLIT_H


#include <crombie2/FileGroup.h>
#include <crombie2/Hist.h>


namespace crombie2 {
  class HistSplit {
  public:
    HistSplit(const FileGroup& group);

    void add (std::vector<Hist> adding);

    void scale (double lumi, double xs);

    std::vector<std::pair<std::string, Hist>>& get_hists ();

    const FileGroup::FileType type;

  private:
    std::vector<std::pair<std::string, Hist>> hists {};
    
  };
}


#endif
