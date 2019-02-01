#ifndef CROMBIE2_JSONREFS_H
#define CROMBIE2_JSONREFS_H


namespace crombie2 {
  /** 
      A simple structure to hold the references
      for JSONAnalyzer during it's "request" stage.
  */
  class JSONRefs {
  public:
    JSONRefs (double& run, double& lumi) :
      run {run}, lumi {lumi} {}
    double& run;
    double& lumi;
  };
}


#endif
