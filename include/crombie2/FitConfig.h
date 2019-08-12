#ifndef CROMBIE2_FITCONFIG_H
#define CROMBIE2_FITCONFIG_H

#include <crombie2/Configurable.h>

#include "TF1.h"
#include "TH1D.h"

namespace crombie2 {
  class FitConfig : public Configurable<std::string> {

  public:
    FitConfig (const std::string& expr);

    std::vector<Configurable<double>> guesses {};

    void resize_guesses ();

    TF1 fit_hist (TH1D* tofit) const;

  };
}

#endif
