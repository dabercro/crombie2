#ifndef CROMBIE2_ONTHEFLYREWEIGHTER_H
#define CROMBIE2_ONTHEFLYREWEIGHTER_H


#include <crombie2/ReweightReader.h>
#include <crombie2/Tree.h>


namespace crombie2 {
  class OnTheFlyReweighter {
  public:
    OnTheFlyReweighter (const ReweightReader& config,
                        Tree& tree);

    /// Get the reweight for the event the Tree is currently on
    double eval ();

  private:
    const std::string index_expr;
    double& index;

    TH1D hist;

    std::shared_ptr<TTreeFormula> expr;
    std::shared_ptr<TTreeFormula> cut;

  };
}


#endif
