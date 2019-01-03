#ifndef CROMBIE2_CONFIGTABLE_H
#define CROMBIE2_CONFIGTABLE_H

#include <gtkmm/table.h>

#include <crombie2/Controller.h>

namespace crombie2 {
  template<typename B = Gtk::VBox> class ConfigTable {
  public:
    ConfigTable (const std::initializer_list<GuiConfigurable*>& configs) :
      confs {configs}, table {size(), 2}
    { table.set_spacings(10); }

    const std::vector<GuiConfigurable*>& get_confs () const { return confs; }

    void draw (Controller& control, Gtk::Box& page) {

      box.set_border_width(10);

      page.pack_start(box, Gtk::PACK_SHRINK);
      box.pack_start(table, Gtk::PACK_SHRINK);
      box.show();
      table.show();

      redraw(control);

    }

    void redraw (Controller& control) {

      table.hide_all();
      table.resize(size(), 2);
      table.show();

      for (unsigned row = 0; row != confs.size(); row++) {
        auto* config = confs[row];
        auto& info = control.register_configurable(*config);
        table.attach(info.label, 0, 1, row, row + 1);
        table.attach(info.entry, 1, 2, row, row + 1);
        info.entry.set_text(info.config.get());
        info.label.show();
        info.entry.show();
      }

    }

    /**
       Add a configurable to the end of the table.
       @param conf A pointer to the configurable to display
    */
    void add_conf (GuiConfigurable* conf) { confs.push_back(conf); }

  private:
    guint size () const { return static_cast<guint>(std::max(confs.size(), 1ul)); }

    std::vector<GuiConfigurable*> confs;
    B box {};
    Gtk::Table table {};

  };
}


#endif
