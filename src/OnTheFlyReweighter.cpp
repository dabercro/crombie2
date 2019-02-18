#include <regex>

#include <crombie2/OnTheFlyReweighter.h>


using namespace crombie2;


OnTheFlyReweighter::OnTheFlyReweighter (const ReweightReader& config,
                                        Tree& tree) :
  index_expr {config.extract_index()},
  index {tree.request(index_expr)},
  hist {config.extract_hist()}
{

  // Assuming index is just a branch
  unsigned max = index_expr != "1" ? tree.max(index_expr) : 1;
  std::regex sub_string {std::string("\\[") + index_expr + "\\]"};

  expressions.reserve(max);
  cuts.reserve(max);

  while (max--) {

    std::string new_string = std::string("[") + std::to_string(max) + "]";

    auto substitute = [&sub_string, &new_string] (const auto& str) {
      return std::regex_replace(str, sub_string, new_string);
    };

    // Create all of the formulas that we want to potentially evaluate
    expressions.push_back(tree.get_formula(substitute(config.expr.get())));
    cuts.push_back(tree.get_formula(substitute(config.cut.get())));

  }

}


double OnTheFlyReweighter::eval () {

  unsigned num = index;

  double output = 1.0;

  for (unsigned i_eval = 0; i_eval < num; i_eval++) {
    if (cuts[i_eval]->EvalInstance())
      output *= hist.GetBinContent(hist.FindBin(expressions[i_eval]->EvalInstance()));
  }

  return output;

}
