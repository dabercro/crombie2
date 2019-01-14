#ifndef CROMBIE2_JOINERCONFIGURABLE_H
#define CROMBIE2_JOINERCONFIGURABLE_H


#include <gtkmm/comboboxtext.h>

#include <crombie2/GuiConfigurable.h>


namespace crombie2 {
  /**
     @brief Holds the expression that joins parts of a cutstring together.
  */
  class JoinerConfigurable : public GuiConfigurable {
  public:
    JoinerConfigurable (const std::string& value);

    JoinerConfigurable (const JoinerConfigurable& other);

    /// Get the label
    std::string label () const override;

    /// Get the value of the configurable
    std::string get () const override;

    /// Set the value of the configurable, using a string
    void set (const std::string& input) override;

    /// Get the widget used to draw and update this
    Gtk::Widget& get_widget () override;

  private:

    void on_update ();

    Gtk::ComboBoxText combobox {};
    std::string value;

  };
}


#endif
