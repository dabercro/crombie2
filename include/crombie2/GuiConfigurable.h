#ifndef CROMBIE2_GUICONFIGURABLE_H
#define CROMBIE2_GUICONFIGURABLE_H

#include <string>

namespace crombie2 {
  /**
     An interface that can be used by the GUI
  */
  class GuiConfigurable {
  public:
    /// Get the label
    virtual std::string label () = 0;

    /// Get the value of the configurable
    virtual std::string get () = 0;

    /// Set the value of the configurable, using a string
    virtual void set (const std::string& input) = 0;

  };
}

#endif
