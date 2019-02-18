#ifndef CROMBIE2_ONTHEFLYREWEIGHTER_H
#define CROMBIE2_ONTHEFLYREWEIGHTER_H


#include <crombie2/OnTheFlyModel.h>
#include <crombie2/Tree.h>

#include "TH1D.h"


namespace crombie2 {
  class OnTheFlyReweighter {
  public:
    OnTheFlyReweighter (const OnTheFlyModel& model,
                        Tree& tree);

    double eval () const;

  private:
    const OnTheFlyModel& model;

    std::vector<std::unique_ptr<TTreeFormula>> expressions {};
    std::vector<std::unique_ptr<TTreeFormula>> cuts {};

    double& index;

    TH1D hist;

    static std::string extract_index (const OnTheFlyModel& model);
    static TH1D extract_hist (const OnTheFlyModel& model);

  };
}


#endif
