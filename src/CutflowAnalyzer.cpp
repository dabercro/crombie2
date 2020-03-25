#include <crombie2/CutflowAnalyzer.h>


using namespace crombie2;


CutflowAnalyzer::CutflowAnalyzer (const Types::strings& cutflow, const std::string& weight) :
  cuts {cutflow},
  weight {weight},
  result (cutflow.size()) {}


void CutflowAnalyzer::make_requests (Tree& tree) {

  for (auto& cut : cuts)
    refs.emplace_back(tree.request(cut), tree.request(weight));

}


void CutflowAnalyzer::notify () {

  unsigned index = 0;
  for (auto& ref : refs) {
    if (ref.cut)
      result[index++] += ref.weight;
    else
      break;
  }

}


const std::vector<double>& CutflowAnalyzer::get_result () const {

  return result;

}
