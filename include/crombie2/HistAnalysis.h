#ifndef CROMBIE2_HISTANALYSIS_H
#define CROMBIE2_HISTANALYSIS_H

#include <crombie2/Hist.h>

namespace crombie2 {
  /**
     @brief Calculates simple values based on histograms

     Not an analyzer.
     Based on the CrombieTool's HistAnalysis class.
  */
  class HistAnalysis {
  public:
    HistAnalysis (const Hist& data, const Hist& mc);
    HistAnalysis (const Hist& data, const Hist& mc, const Hist& background);

    /// Create reweight histogram
    void reweight (bool normalize, const std::string& output) const;

  private:
    bool has_background {false};

    Hist data;
    Hist mc;
    Hist background {};

  };
}


#endif
