#ifndef CROMBIE2_CONTROLLER_H
#define CROMBIE2_CONTROLLER_H


#include <gtkmm/button.h>
#include <gtkmm/comboboxentrytext.h>

#include <crombie2/ConfigModel.h>
#include <crombie2/ConfigPage.h>


namespace crombie2 {
  /**
     @brief An abstract class to handle the relation between the GUI and a ConfigModel.

     Provides the user (via the ConfigPage) with buttons to save and load every underlying model.
  */
  class Controller {
  public:

    Controller (ConfigPage& page, ConfigModel& model);
    virtual ~Controller () = default;

    /// Get a reference back to the page for something else to draw on
    ConfigPage& get_page ();

    void on_update ();

  protected:

    /// Reference to page that is drawn on
    ConfigPage& page;

    virtual void redraw () = 0;

    static const std::string last_tag;

  private:

    /// Model that is saved and loaded from Controller interface
    ConfigModel& model;

    void on_save ();
    void on_load ();

    void on_export ();
    void on_import ();

    /// Updates the list of tags to select from
    void update_entries ();

    Gtk::HBox updatebox {};

    Gtk::Button exportbutton {"Export"};
    Gtk::Button importbutton {"Import"};

    Gtk::Button updatebutton {"Update"};
    Gtk::Button savebutton {"Save Tag"};
    Gtk::Button loadbutton {"Load Tag"};
    Gtk::ComboBoxEntryText tagentry {};

  };
}


#endif
