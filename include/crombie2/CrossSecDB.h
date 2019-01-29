#ifndef CROMBIE2_CROSSSECDB_H
#define CROMBIE2_CROSSSECDB_H


#include <crombie2/Configurable.h>
#include <crombie2/SimpleModel.h>


namespace crombie2 {
  /**
     @brief Connects to cross section database to get cross section values.
  */
  class CrossSecDB : public SimpleModel {
  public:
    CrossSecDB ();

    std::string get_name () const override;

    /**
       @brief Get the cross section of a dataset.
       @param dataset Primary dataset name
       @returns The cross section if in the database, else 0
    */
    double get_xs (const std::string& dataset);

    /// The only parameter is the script used to get the cross section from
    Configurable<std::string> executable {"Cross Section Getter", ""};

  };
}


#endif
