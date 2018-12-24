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
      relabel{[label] (const C&) {return label;}}, value{value} {}

    /**
       Create a configurable with a dynamic label
       @param relabel The function that takes the value as input and makes a label
       @param value The value of the configurable
    */
    Configurable(const labelfunc& relabel, const C& value) :
      relabel{relabel}, value{value} {}

    std::string label () override {
      return relabel(value);
    }

    std::string get () override {
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
    const labelfunc relabel;
    C value;

  };

}


#endif
