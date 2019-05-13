#ifndef CROMBIE2_TEXTCONFIGURABLE_H
#define CROMBIE2_TEXTCONFIGURABLE_H


#include <gtkmm/entry.h>

#include <crombie2/GuiConfigurable.h>


namespace crombie2 {
  /**
     @brief A GuiConfigurable that is edited through a Gtk::Entry.

     The value is immediately updated when the contents of Gtk::Entry is edited.
     This is still an abstract class, but implements GuiConfigurable::get_widget.
  */
  class TextConfigurable : public GuiConfigurable {
  public:

    TextConfigurable (const std::string& tooltip = "");
    /// Copy constructor does not copy the Gtk::Entry widget
    TextConfigurable (const TextConfigurable& other);

    /// Get a reference to an underlying Gtk::Entry
    Gtk::Widget& get_widget () override;

  protected:
    /// The box that holds the entry
    Gtk::Entry entry {};

  private:
    /// Updates the value of the configurable when the entry is edited by the user.
    void on_update ();

  };
}


#endif
