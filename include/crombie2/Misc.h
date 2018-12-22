#ifndef CROMBIE2_MISC_H
#define CROMBIE2_MISC_H

#include <string>
#include <vector>

#include "crombie2/Types.h"

namespace crombie2 {
  namespace Misc {

    /**
       Split the contents of a string into multiple strings.
       This is different than crombie::Misc::split because it can split over multiple spaces,
       while spilt_string only splits over one character at a time.
     */
    Types::strings tokenize(const std::string& str);


    /// Splits a string.
    Types::strings split(const std::string& str, const std::string& delim = "\n");


    /// Get the output of a shell command
    std::string shell(const std::string& cmd);


    /// Get an environment variable by name, with an optional fallback value
    std::string env(const std::string& variable, const std::string& fallback = "");

    template<typename O, typename C, typename F>
      std::vector<O> comprehension (const C& container, const F& func) {
      std::vector<O> output {};
      for (auto& iter : container)
        output.push_back(func(iter));
      return output;
    }

  }
}

#endif
