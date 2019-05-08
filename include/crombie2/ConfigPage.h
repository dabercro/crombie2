#ifndef CROMBIE2_CONFIGPAGE_H
#define CROMBIE2_CONFIGPAGE_H

#include <string>

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>

namespace crombie2 {
  class Controller;
  class ConfigModel;

  /**
     @brief Page that shows up as a tab in the MainWindow
  */
  class ConfigPage : public Gtk::VBox {
  public:
    enum class Scroll {
      DOWN,
      UP,
      LEFT,
      RIGHT
    };

    /**
       @param label The text to put in the box tab
    */
    ConfigPage (const std::string& label = "");

    ConfigPage& operator=(const ConfigPage& other);

    /// Get the label
    const std::string& get_label ();

    /// Get the box that is inside of the scroll window for drawing
    Gtk::VBox& box ();

    void set_controller_model (Controller& controller, ConfigModel& model);

    Controller& get_controller ();
    ConfigModel& get_model ();

    void scroll (Scroll direction);

    void draw (Gtk::Widget& widget);

  private:

    std::string label;               ///< The label for the tab in the MainWindow
    Gtk::ScrolledWindow scrolled {}; ///< For the middle of the page
    Gtk::VBox internalbox {};        ///< A box for drawing inside of the scroll box

    Controller* controller_ptr {};
    ConfigModel* model_ptr {};

  };
}


#endif
