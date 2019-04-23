#ifndef CROMBIE2_CONFIGURABLE_H
#define CROMBIE2_CONFIGURABLE_H

#include <sstream>
#include <type_traits>

#include <crombie2/TextConfigurable.h>

namespace crombie2 {

  /**
     @brief A TextConfigurable that can hold most types of data via templating
  */
  template<typename C> class Configurable : public TextConfigurable {
  public:

    /// Create a configurable with an empty label
    Configurable () {}

    /**
       Create a configurable with a static label
       @param label The label for this configurable
       @param value The initial value of the configurable
    */
    Configurable (const std::string& label, const C& value) :
      name{label}, value{value} {}

    /// Get the label to write on the table
    std::string label () const override {
      return name;
    }

    /// Get the value in string form
    std::string get () const override {
      if constexpr (std::is_same<C, std::string>::value)
        return value;

      std::stringstream ss;
      ss << value;
      return ss.str();
    }

    /// Set the value using a string
    void set (const std::string& input) override {
      if constexpr (std::is_same<C, std::string>::value)
        value = input;
      else {
        std::stringstream ss;
        ss.str(input);
        ss >> value;
      }
    }

    /// Allows the Configurable to be compared directly or substituted in places
    operator C () const { return value; }

    /// Sets the value of the Configurable and updates the widget for the user
    C operator= (C val) {
      auto text = std::to_string(val);
      // Take away all of the zeros
      while (text.back() == '0')
        text.pop_back();

      entry.set_text(text);
      return value = val;
    }

  private:
    std::string name {};   ///< Name for the label shown by ConfigTable
    C value {};            ///< Value being held

  };

}


#endif
