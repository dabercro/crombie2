#ifndef CROMBIE2_COMPARE_H
#define CROMBIE2_COMPARE_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>


namespace crombie2 {
  class Compare : public ConfigTable {
  public:
    Compare () : ConfigTable {
      &name, &legend, &style
    } {}
    Compare (const Compare& other);
    virtual ~Compare () = default;

    Configurable<std::string> name {"File Name", "", "Should be '<selection>_<plotvar>'"};
    Configurable<std::string> legend {"Legend Entry", ""};
    Configurable<int> style {"Style", 0};

  };

}


#endif
