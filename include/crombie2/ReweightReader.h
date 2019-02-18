#ifndef CROMBIE2_REWEIGHTREADER_H
#define CROMBIE2_REWEIGHTREADER_H


#include <crombie2/Configurable.h>
#include <crombie2/ConfigTable.h>


namespace crombie2 {
  class ReweightReader {

  public:

    ReweightReader () = default;
    ReweightReader (const ReweightReader& other);
    virtual ~ReweightReader () = default;

    Configurable<std::string> expr {"Bin Expression", ""};
    Configurable<std::string> cut {"Cut", "1"};
    Configurable<std::string> file {"File Name", ""};
    Configurable<std::string> hist {"Hist Name", ""};

    ConfigTable table {
      &expr, &cut, &file, &hist
    };

  };
}


#endif
