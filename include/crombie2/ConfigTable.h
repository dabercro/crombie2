#ifndef CROMBIE2_CONFIGTABLE_H
#define CROMBIE2_CONFIGTABLE_H

#include <vector>

#include <gtkmm/table.h>

#include <crombie2/ConfigPage.h>
#include <crombie2/Controller.h>
#include <crombie2/GuiConfigurable.h>

namespace crombie2 {
  class ConfigTable {
  public:
    ConfigTable (const std::initializer_list<GuiConfigurable*>& configs);

    const std::vector<GuiConfigurable*>& get_confs () const;

    void draw (Controller& control, ConfigPage& page);

  private:
    const std::vector<GuiConfigurable*> confs;
    Gtk::Table table {};

  };
}


#endif
