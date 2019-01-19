#ifndef CROMBIE2_CROSSSECDB_H
#define CROMBIE2_CROSSSECDB_H


#include <crombie2/Configurable.h>
#include <crombie2/SimpleModel.h>


namespace crombie2 {
  class CrossSecDB : public SimpleModel {
  public:
    CrossSecDB ();

    std::string get_name () const override;

    double get_xs (const std::string& dataset);

    Configurable<std::string> executable {"Cross Section Getter", ""};

  };
}


#endif
