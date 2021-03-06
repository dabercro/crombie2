#ifndef CROMBIE2_SELECTION_H
#define CROMBIE2_SELECTION_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>


namespace crombie2 {

  class Selection {
  public:
    Selection (const std::string& cut = "",
               const std::string& data = "",
               const std::string& mc = "",
               const std::string& name = "",
               const std::string& control = "");
    Selection (const Selection& other);

    virtual ~Selection () = default;

    Configurable<std::string> cut;
    Configurable<std::string> data_weight;
    Configurable<std::string> mc_weight;
    Configurable<std::string> name;
    Configurable<std::string> control_plot;
    ConfigTable table {
      &cut, &data_weight, &mc_weight, &name, &control_plot
    };

    std::string get_name () const;

  };

}


#endif
