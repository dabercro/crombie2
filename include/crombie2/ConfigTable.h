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
    virtual ~ConfigTable () = default;

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

    /// Give the configurable values in a one-line string
    std::string dump () const;

    /// Given a space-separated line, loads the values into the table
    void fill (const std::string& line) const;

    void clear ();

  protected:
    /// Copy another ConfigTable to this one
    void copy (const ConfigTable& other);

  private:
    /**
       A Gtk::Table must have at least one row.
       This is just a hack to get either the real needed size or one (1),
       whichever is greater.
    */
    guint size () const;

    /// Pointers to the configurables to draw
    std::vector<GuiConfigurable*> confs;

    /// Each table has this frame drawn around it
    Gtk::Frame frame {};
    /// The internal table to draw
    Gtk::Table table;

    const bool horizontal;

  };
}


#endif
