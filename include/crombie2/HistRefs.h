#ifndef CROMBIE2_HISTREFS_H
#define CROMBIE2_HISTREFS_H


namespace crombie2 {
  /** 
      A simple structure to hold the references
      for HistAnalyzer during it's "request" stage.
  */
  class HistRefs {
  public:
    HistRefs (double& cut, double& expr, double& weight, double& sub) :
    cut {cut}, expr {expr}, weight {weight}, sub {sub} {}
    double& cut;
    double& expr;
    double& weight;
    double& sub;
  };
}


#endif
