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


bool Tree::next() {

  if (ientry == nentries)
    return false;

  tree->GetEntry(ientry++);

  for (auto& form : forms)
    form.second.first = form.second.second->EvalInstance();

  return true;

}


double& Tree::request (const std::string& expr) {
  auto i_form = forms.find(expr);
  if (i_form != forms.end())
    return i_form->second.first;

  // Update set of needed branches
  for (auto* branch : *(tree->GetListOfBranches())) {
    auto name = branch->GetName();
    if (expr.find(name) != std::string::npos) {
      // Only save branches that are really in the expression
      const std::regex regexpr {std::string("\\b") + name + "\\b"};
      std::smatch matches;
      if (std::regex_search(expr, matches, regexpr))
        tree->SetBranchStatus(name, 1);
    }
  }

  // Put the formula in, in a thread-safe way
  Misc::lock();
  TTreeFormula* form = new TTreeFormula(expr.data(), expr.data(), tree);
  Misc::unlock();

  auto output = forms.insert({expr, std::make_pair(0.0, form)});

  return output.first->second.first;

}
