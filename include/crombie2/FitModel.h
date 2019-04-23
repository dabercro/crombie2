#ifndef CROMBIE2_FITMODEL_H
#define CROMBIE2_FITMODEL_H

#include <crombie2/ConfigModel.h>
#include <crombie2/FitConfig.h>
#include <crombie2/RemoveList.h>

namespace crombie2 {
  class FitModel : public ConfigModel {

  public:

    std::string get_name () const override;

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

    RemoveList<FitConfig> fits {};

  };
}

#endif
