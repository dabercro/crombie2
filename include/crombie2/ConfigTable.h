#ifndef CROMBIE2_CONFIGTABLE_H
#define CROMBIE2_CONFIGTABLE_H


#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>

#include <crombie2/GuiConfigurable.h>


namespace crombie2 {
  /**
     @brief Container for GuiConfigurable objects that handles drawing on page
  */
  class ConfigTable {
  public:
    ConfigTable (const std::initializer_list<GuiConfigurable*>& configs, const bool horizontal = false);

    /// Get a collection of GuiConfigurable pointers
    const std::vector<GuiConfigurable*>& get_confs () const;

    /**
       Draw this table
       @param page Is the location where to place the table using pack_start
    */
    void draw (Gtk::Box& page);

    void redraw ();

    /**
       Add a configurable to the end of the table.
       @param conf A pointer to the configurable to display
    */
    void add_conf (GuiConfigurable* conf);

  private:
    guint size () const;

    std::vector<GuiConfigurable*> confs;
    Gtk::Frame frame {};
    Gtk::Table table;

    const bool horizontal;

  };
}


#endif
