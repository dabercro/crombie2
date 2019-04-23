#ifndef CROMBIE2_FITCONFIG_H
#define CROMBIE2_FITCONFIG_H

#include <crombie2/Configurable.h>


namespace crombie2 {
  class FitConfig : public Configurable<std::string> {

  public:
    FitConfig (const std::string& expr);

    std::vector<Configurable<double>> guesses {};

  private:

    void resize_guesses ();

  };
}

#endif
