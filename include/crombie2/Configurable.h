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
    /**
       Create a configurable with a static label
       @param label The label for this configurable
       @param value The value of the configurable
    */
    Configurable (const std::string& label, const C& value) :
      name{label}, value{value} {}

    std::string label () const override {
      return name;
    }

    std::string get () const override {
      if constexpr (std::is_same<C, std::string>::value)
        return value;

      std::stringstream ss;
      ss << value;
      return ss.str();
    }

    void set (const std::string& input) override {
      if constexpr (std::is_same<C, std::string>::value)
        value = input;
      else {
        std::stringstream ss;
        ss.str(input);
        ss >> value;
      }
    }

    operator C () const { return value; }

    C operator= (C val) {
      entry.set_text(std::to_string(val));
      return value = val;
    }

  private:
    std::string name;
    C value;

  };

}


#endif
