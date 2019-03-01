#ifndef CROMBIE2_MAINWINDOW_H
#define CROMBIE2_MAINWINDOW_H


#include <map>

#include <gtkmm/notebook.h>
#include <gtkmm/window.h>

#include <crombie2/MainController.h>


namespace crombie2 {
  class MainWindow : public Gtk::Window {

  public:
    MainWindow ();

  private:

    static std::map<std::string, ConfigPage> init_map ();

    void add_page (ConfigPage& page);

    Gtk::Notebook book {};

    std::map<std::string, ConfigPage> pagemap {init_map()};

    ConfigPage jobpage {"Jobs"};

    MainController maincontrol {
      pagemap,
      jobpage
    };

    bool on_key_press_event (GdkEventKey* event) override;
    bool on_key_release_event (GdkEventKey* event) override;

    bool cntrl {false};

  };
}

#endif
