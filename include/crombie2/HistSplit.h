#ifndef CROMBIE2_HISTSPLIT_H
#define CROMBIE2_HISTSPLIT_H


#include <crombie2/FileGroup.h>
#include <crombie2/Hist.h>


namespace crombie2 {
  class HistSplit {
  public:
    HistSplit(const FileGroup& group);

    void add (std::vector<Hist> adding);

    std::vector<Hist>& get_hists ();

  private:
    std::vector<Hist> hists {};
    
  };
}


#endif
