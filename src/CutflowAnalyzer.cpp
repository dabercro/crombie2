#include <crombie2/CutflowAnalyzer.h>


using namespace crombie2;


CutflowAnalyzer::CutflowAnalyzer (const Types::strings& cutflow) :
  cuts {cutflow},
  result (cutflow.size()) {}


void CutflowAnalyzer::make_requests (Tree& tree) {

  for (auto& cut : cuts)
    refs.emplace_back(tree.request(cut));

}


void CutflowAnalyzer::notify () {

  unsigned index = 0;
  for (auto& ref : refs) {
    if (ref.cut)
      result[index++] += 1;
    else
      break;
  }

}


const std::vector<long>& CutflowAnalyzer::get_result () const {

  return result;

}
