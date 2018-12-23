#ifndef CROMBIE2_CONFIGPAGE_H
#define CROMBIE2_CONFIGPAGE_H

#include <string>

#include <gtkmm/box.h>


namespace crombie2 {
  class ConfigPage : public Gtk::VBox {
  public:
    ConfigPage (const std::string& label);

    /// Get the label
    const std::string& get_label ();

  private:
    const std::string label;

  };
}


#endif
