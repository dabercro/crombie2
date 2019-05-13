#ifndef CROMBIE2_GUICONFIGURABLE_H
#define CROMBIE2_GUICONFIGURABLE_H


#include <string>

#include <gtkmm/label.h>
#include <gtkmm/widget.h>


namespace crombie2 {
  /**
     @brief An interface that can be used by the GUI
  */
  class GuiConfigurable {
  public:
    GuiConfigurable (const std::string& tooltip = "");
    virtual ~GuiConfigurable () {}

    /// Get the label
    virtual std::string label () const = 0;

    /// Get the value of the configurable
    virtual std::string get () const = 0;

    /// Set the value of the configurable, using a string
    virtual void set (const std::string& input) = 0;

    /// Get the widget used to draw and update this object's values
    virtual Gtk::Widget& get_widget () = 0;

    /// Get the label object
    Gtk::Label& get_label ();

  protected:
    Gtk::Label label_obj {};

  };
}

#endif
