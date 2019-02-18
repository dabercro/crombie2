#include <regex>

#include <crombie2/Misc.h>
#include <crombie2/Tree.h>


using namespace crombie2;


Tree::Tree (const std::string& infile, const std::string& treename) :
  file {TFile::Open(infile.data())},
  tree{get<TTree>(treename)},
  nentries{tree->GetEntries()}
{

  tree->SetBranchStatus("*", 0);

}


Tree::~Tree () {

  file->Close();
  delete file;

}


std::shared_ptr<TTreeFormula> Tree::get_formula (const std::string& expr) {

  // Update set of needed branches
  for (auto* branch : *(tree->GetListOfBranches())) {
    auto name = branch->GetName();
    if (expr.find(name) != std::string::npos) {
      // Only save branches that are really in the expression
      const std::regex regexpr {std::string("\\b") + name + "\\b"};
      std::smatch matches;
      if (std::regex_search(expr, matches, regexpr)) {
        if (not tree->GetBranchStatus(name))
          branches_to_read.push_back(tree->GetBranch(name));

        tree->SetBranchStatus(name, 1);
      }
    }
  }

  // Put the formula in, in a thread-safe way
  Misc::lock();
  auto output = std::make_shared<TTreeFormula>(expr.data(), expr.data(), tree);
  Misc::unlock();

  return output;

}


double& Tree::request (const std::string& expr) {
  auto i_form = forms.find(expr);
  if (i_form != forms.end())
    return i_form->second.first;

  auto output = forms.insert({expr, std::make_pair(0.0, get_formula(expr))});

  return output.first->second.first;
}


double Tree::max (const std::string& branch) {

  return tree->GetMaximum(branch.data());

}
