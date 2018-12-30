#ifndef CROMBIE2_CONFIGURABLE_H
#define CROMBIE2_CONFIGURABLE_H

#include <sstream>
#include <functional>

#include <crombie2/GuiConfigurable.h>

namespace crombie2 {

  template<typename C> class Configurable : public GuiConfigurable {

    using labelfunc = std::function<std::string(const C&)>;

  public:
    /**
       Create a configurable with a static label
       @param label The label for this configurable
       @param value The value of the configurable
    */
    Configurable(const std::string& label, const C& value) :
      name{label}, value{value} {}

    std::string label () const override {
      return name;
    }

    std::string get () const override {
      std::string o;
      std::stringstream ss;
      ss << value;
      ss >> o;
      return o;
    }

    void set (const std::string& input) override {
      std::stringstream ss;
      ss << input;
      ss >> value;
    }

  private:
    std::string name;
    C value;

  };

}


#endif
