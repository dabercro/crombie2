#ifndef CROMBIE2_TEXTCONFIGURABLE_H
#define CROMBIE2_TEXTCONFIGURABLE_H


#include <gtkmm/entry.h>

#include <crombie2/GuiConfigurable.h>


namespace crombie2 {
  class TextConfigurable : public GuiConfigurable {
  public:
    TextConfigurable ();
    TextConfigurable (const TextConfigurable& other);

    Gtk::Widget& get_widget () override;

  private:
    void on_update ();

    /// The box that holds the entry
    Gtk::Entry entry {};
  };
}


#endif
