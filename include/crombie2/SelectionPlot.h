#ifndef CROMBIE2_SELECTIONPLOT_H
#define CROMBIE2_SELECTIONPLOT_H


#include <crombie2/ConfigTable.h>


namespace crombie2 {
  class SelectionPlot : public ConfigTable {
  public:
    SelectionPlot () : ConfigTable {
      &selection, &plot
    } {}
    SelectionPlot (const SelectionPlot& other) : SelectionPlot() { copy(other); }
    virtual ~SelectionPlot () = default;

    Configurable<std::string> selection {"Region", ""};
    Configurable<std::string> plot {"Variable", ""};

  };
}


#endif
