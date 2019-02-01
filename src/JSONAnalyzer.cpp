#include <crombie2/JSONAnalyzer.h>


using namespace crombie2;


JSONAnalyzer::JSONAnalyzer (const JSONModel& model) :
  model {model} {}


void JSONAnalyzer::make_requests (Tree& tree) {

  ref = std::make_unique<JSONRefs>(tree.request(model.runnum),
                                   tree.request(model.luminum));

}


void JSONAnalyzer::notify () {

  result.add(ref->run, ref->lumi);

}


const LumiSelection& JSONAnalyzer::get_result () const {

  return result;

}

