#ifndef CROMBIE2_CONFIGTABLE_H
#define CROMBIE2_CONFIGTABLE_H

#include <gtkmm/table.h>

#include <crombie2/Controller.h>

namespace crombie2 {
  class ConfigTable {
  public:
    ConfigTable (const std::initializer_list<GuiConfigurable*>& configs);

    const std::vector<GuiConfigurable*>& get_confs () const;

    void draw (Controller& control, Gtk::Box& page);

    void redraw (Controller& control);

  private:
    const std::vector<GuiConfigurable*> confs;
    Gtk::VBox box {};
    Gtk::Table table {};

  };
}


#endif
