#ifndef CROMBIE2_LEGENDENTRY_H
#define CROMBIE2_LEGENDENTRY_H

#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>

namespace crombie2 {
  class LegendEntry {
  public:
    LegendEntry () = default;
    LegendEntry (const LegendEntry& other) :
    datacard {other.datacard}, legend {other.legend}, cut {other.cut}, style {other.style} {}

    Configurable<std::string> datacard {"Datacard Entry", ""};
    Configurable<std::string> legend {"Legend Entry", ""};
    Configurable<std::string> cut {"Cut", "1"};
    Configurable<short> style {"Plot Style", 1};
    ConfigTable table {{
      &datacard, &legend, &cut, &style
    }, true};

  };
}

#endif
