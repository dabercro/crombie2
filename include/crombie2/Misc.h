#ifndef CROMBIE2_MISC_H
#define CROMBIE2_MISC_H

#include <set>

#include <crombie2/Types.h>

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

    bool confirm (const std::string& message);

    /**
       @brief Returns the a cut with a variable taken out.

       The function only removes expressions where the variable name is to the left of an operator.
    */
    std::string nminus1(const std::string& var, const std::string& cut);

    /// Displays messages for user
    void message (const std::string& primary, const std::string& secondary = "");


    enum class uncdir {
      UP,
      DOWN
    };

    std::string uncertify (const std::set<std::string>& branchlist, const std::string& expr, const std::string& unc, uncdir dir);


    /** 
       @brief Check for value in a comma-separated list.

       If tocheck actually holds an empty field, then it's assumed the user wants to use all values.
       In that case, this function always returns true.

       @param val The value that we want to determine is present or not
       @param tocheck The comma-separated list to search
       @returns if the value is present, or if tocheck has an empty value
    */
    bool check_comma_field (const std::string& val, const std::string& tocheck);


    std::string replace (const std::string& input, const std::string& target, const std::string& newstr);


    void draw_progress(unsigned progress, unsigned max);


  }
}

#endif
