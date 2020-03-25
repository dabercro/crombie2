#ifndef CROMBIE2_CUTFLOWREFS_H
#define CROMBIE2_CUTFLOWREFS_H


namespace crombie2 {
  /** 
      A simple structure to hold the references
      for CutflowAnalyzer during it's "request" stage.
  */
  class CutflowRefs {
  public:
    CutflowRefs (double& cut, double& weight) :
      cut {cut},
      weight {weight} {}
    double& cut;
    double& weight;
  };
}


#endif
