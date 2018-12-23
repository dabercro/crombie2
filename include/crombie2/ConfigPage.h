#ifndef CROMBIE2_CONFIGPAGE_H
#define CROMBIE2_CONFIGPAGE_H

#include <string>

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>

namespace crombie2 {
  class ConfigPage : public Gtk::VBox {
  public:
    ConfigPage (const std::string& label);

    /// Get the label
    const std::string& get_label ();

    Gtk::VBox& box ();

  private:
    const std::string label;
    Gtk::ScrolledWindow scrolled {};
    Gtk::VBox internalbox {};

  };
}


#endif
