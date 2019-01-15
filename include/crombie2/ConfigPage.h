#ifndef CROMBIE2_CONFIGPAGE_H
#define CROMBIE2_CONFIGPAGE_H

#include <string>

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>

namespace crombie2 {
  /**
     @brief Page that shows up as a tab in the MainWindow
  */
  class ConfigPage : public Gtk::VBox {
  public:
    /**
       @param label The text to put in the box tab
    */
    explicit ConfigPage (const std::string& label);

    /// Get the label
    const std::string& get_label ();

    /// Get the box that is inside of the scroll window for drawing
    Gtk::VBox& box ();

  private:

    const std::string label;         ///< The label for the tab in the MainWindow
    Gtk::ScrolledWindow scrolled {}; ///< For the middle of the page
    Gtk::VBox internalbox {};        ///< A box for drawing inside of the scroll box

  };
}


#endif
