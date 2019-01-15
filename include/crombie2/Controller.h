#ifndef CROMBIE2_CONTROLLER_H
#define CROMBIE2_CONTROLLER_H


#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>

#include <crombie2/ConfigModel.h>
#include <crombie2/ConfigPage.h>


namespace crombie2 {
  /**
     @brief An abstract class to handle the relation between the GUI and a ConfigModel.

     Provides the user (via the ConfigPage) with buttons to save and load every underlying model.
  */
  class Controller {
  public:

    /// Hold a reference to the page to draw on
    Controller (ConfigPage& page, ConfigModel& model);
    virtual ~Controller () = default;


    /// Get a reference back to the page for something else to draw on
    ConfigPage& get_page ();

    void on_update ();

  protected:

    ConfigPage& page;

    virtual void redraw () = 0;

  private:

    static const std::string last_tag;

    ConfigModel& model;

    void on_save ();
    void on_load ();

    void update_entries ();

    Gtk::HBox updatebox {};

    Gtk::Button updatebutton {"Update"};
    Gtk::Button savebutton {"Save Tag"};
    Gtk::Button loadbutton {"Load Tag"};
    Gtk::ComboBoxText tagentry {true};

  };
}

#endif
