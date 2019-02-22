#include <regex>

#include <crombie2/OnTheFlyReweighter.h>


using namespace crombie2;


OnTheFlyReweighter::OnTheFlyReweighter (const ReweightReader& config,
                                        Tree& tree) :
  index_expr {config.extract_index()},
  index {tree.request(index_expr)},
  hist {config.extract_hist()},
  expr {tree.get_formula(config.extract_expr())},
  cut {tree.get_formula(config.extract_cut())} {}


double OnTheFlyReweighter::eval () {

  unsigned num = index;

  double output = 1.0;

  cut->GetNdata();
  expr->GetNdata();

  for (unsigned i_eval = 0; i_eval < num; i_eval++) {

    if (cut->EvalInstance(i_eval))
      output *= hist.GetBinContent(hist.FindBin(expr->EvalInstance(i_eval)));

  }

  return output;

}
