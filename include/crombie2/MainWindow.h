#ifndef CROMBIE2_MAINWINDOW_H
#define CROMBIE2_MAINWINDOW_H


#include <memory>

#include <gtkmm/notebook.h>
#include <gtkmm/window.h>

#include <crombie2/MainController.h>


namespace crombie2 {
  class MainWindow : public Gtk::Window {

  public:
    /// Get a reference to the main window of the program
    static MainWindow& get ();

    MainWindow ();

  private:

    void add_page (ConfigPage& page);

    Gtk::Notebook book {};

    ConfigPage globals {"Globals"};
    ConfigPage files {"Files"};
    ConfigPage plots {"Plots"};
    ConfigPage selections {"Selections"};
    ConfigPage uncertainties {"Uncertainties"};
    ConfigPage jobpage {"Jobs"};

    MainController maincontrol {
      globals,
      files,
      plots,
      selections,
      uncertainties,
      jobpage
    };

    static std::unique_ptr<MainWindow> main;

  };
}

#endif
