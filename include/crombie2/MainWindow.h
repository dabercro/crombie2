#ifndef CROMBIE2_MAINWINDOW_H
#define CROMBIE2_MAINWINDOW_H


#include <gtkmm/notebook.h>
#include <gtkmm/window.h>

#include <crombie2/ConfigPage.h>

namespace crombie2 {
  class MainWindow : public Gtk::Window {

  public:
    MainWindow ();

  private:
    void add_page (ConfigPage& page);

    Gtk::Notebook book {};

    ConfigPage selections {"Selections"};
  };
}

#endif
