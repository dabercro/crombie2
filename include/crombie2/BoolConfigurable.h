#ifndef CROMBIE2_BOOLCONFIGURABLE_H
#define CROMBIE2_BOOLCONFIGURABLE_H


#include <gtkmm/checkbutton.h>

#include <crombie2/GuiConfigurable.h>


namespace crombie2 {
  /**
     @brief An interface that can be used by the GUI
  */
  class BoolConfigurable : public GuiConfigurable {
  public:
    BoolConfigurable (const std::string& label);
    BoolConfigurable (const BoolConfigurable& other);

    /// Get the label
    std::string label () const override;

    /// Get the value of the configurable
    std::string get () const override;

    /**
       @brief Set the value of the configurable.

       A value of "0" or "" is false. Anything else is true.
    */
    void set (const std::string& input) override;

    /// Get the widget used to draw and update this object's values
    Gtk::Widget& get_widget () override;

    operator bool () const;

  private:
    const std::string name;

    Gtk::CheckButton checkbox {};

    bool value {false};

    void on_update ();

  };
}



#endif
