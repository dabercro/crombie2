#ifndef CROMBIE2_CONFIGREF_H
#define CROMBIE2_CONFIGREF_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>

#include <crombie2/GuiConfigurable.h>


namespace crombie2 {

  class ConfigRef {
  public:
    ConfigRef (GuiConfigurable& config, const std::string& label);
    GuiConfigurable& config;
    Gtk::Label label;
    Gtk::Entry entry {};
    Gtk::HBox box {};
    void show ();
  };

}


#endif
