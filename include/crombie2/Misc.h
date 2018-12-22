#ifndef CROMBIE_MISC_H
#define CROMBIE_MISC_H

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>
#include <vector>

#include "crombie2/Types.h"

namespace crombie2 {
  namespace Misc {

    /**
       Split the contents of a string into multiple strings.
       This is different than crombie::Misc::split because it can split over multiple spaces,
       while spilt_string only splits over one character at a time.
     */
    Types::strings tokenize(const std::string& str) {
      std::istringstream ss {str};
      Types::strings output {
        std::istream_iterator<std::string>{ss},
        std::istream_iterator<std::string>{}
      };
      return output;
    }


    /// Splits a string.
    Types::strings split(const std::string& str, const std::string& delim = "\n") {
      Types::strings output;
      std::string::size_type prev = 0;
      for(auto pos = str.find(delim);
          pos != std::string::npos;
          prev = pos + delim.size(), pos = str.find(delim, prev))
        output.push_back(str.substr(prev, pos - prev));

      auto last = str.substr(prev);
      if (last.size())
        output.push_back(last);


      return output;
    }


    /// Get the output of a shell command
    std::string shell(const std::string& cmd) {
      std::array<char, 128> buffer;
      std::string output;
      std::shared_ptr<FILE> pipe(popen(cmd.data(), "r"), pclose);
      if (not pipe)
        throw std::runtime_error("popen() failed");
      while(not feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()))
          output += buffer.data();
      }
      return output;
    }


    /// Get an environment variable by name, with an optional fallback value
    std::string env(const std::string& variable, const std::string& fallback = "") {
      auto* output = getenv(variable.data());
      if (output)
        return std::string(output);
      if (not fallback.size())
        throw std::runtime_error(std::string("Requesting non-existent variable '") + variable + "' with no fallback");
      return std::string(fallback);
    }

  }
}

#endif
