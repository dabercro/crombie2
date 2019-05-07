#ifndef CROMBIE2_DATACARDMODEL_H
#define CROMBIE2_DATACARDMODEL_H


#include <crombie2/BoolConfigurable.h>
#include <crombie2/Configurable.h>
#include <crombie2/SimpleModel.h>


namespace crombie2 {
  /**
     @brief A SimpleModel holding information for styling plots
  */
  class DatacardModel : public SimpleModel {
  public:
    DatacardModel ();
    DatacardModel (const DatacardModel& other);

    std::string get_name () const override;

    /// The directory to output plots
    Configurable<std::string> outdir {"Datacard Output", "datacard"};

  };

}


#endif
