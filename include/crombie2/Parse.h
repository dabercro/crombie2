#ifndef CROMBIE2_PARSE_H
#define CROMBIE2_PARSE_H

#include <istream>

#include <crombie2/Types.h>

namespace crombie2 {
  namespace Parse {

    /// Parse an input stream and return a list of parsed lines, with empty lines removed
    Types::strings parse (std::istream& is);

  }
}

#endif
