#ifndef CROMBIE2_JSONMODEL_H
#define CROMBIE2_JSONMODEL_H


#include <crombie2/Configurable.h>
#include <crombie2/SimpleModel.h>
#include <crombie2/Tree.h>


namespace crombie2 {
  /**
     @brief A SimpleModel holding information for making JSONs of run-lumi
  */
  class JSONModel : public SimpleModel {
  public:
    JSONModel ();
    JSONModel (const JSONModel& other);

    std::string get_name () const override;

    Configurable<std::string> runnum {"Run Expression", "runNumber"};

    Configurable<std::string> luminum {"Lumi Expression", "lumiNumber"};

    bool is_valid (Tree& tree) const;

  };

}


#endif
