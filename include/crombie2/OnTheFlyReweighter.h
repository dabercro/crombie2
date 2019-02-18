#ifndef CROMBIE2_ONTHEFLYREWEIGHTER_H
#define CROMBIE2_ONTHEFLYREWEIGHTER_H


#include <crombie2/OnTheFlyModel.h>
#include <crombie2/Tree.h>

#include "TH1D.h"


namespace crombie2 {
  class OnTheFlyReweighter {
  public:
    OnTheFlyReweighter (const ReweightReader& config,
                        Tree& tree);

    /// Get the reweight for the event the Tree is currently on
    double eval ();

  private:
    std::vector<std::shared_ptr<TTreeFormula>> expressions {};
    std::vector<std::shared_ptr<TTreeFormula>> cuts {};

    const std::string index_expr;
    double& index;

    TH1D hist;

  };
}


#endif
