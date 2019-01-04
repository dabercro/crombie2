#ifndef CROMBIE2_MINIFILECONTROLLER_H
#define CROMBIE2_MINIFILECONTROLLER_H


#include <gtkmm/buttonbox.h>
#include <gtkmm/radiobutton.h>

#include <crombie2/FileGroup.h>


namespace crombie2 {
  class MiniFileController {
  public:
    MiniFileController(Controller& controller, FileGroup& filegroup, Gtk::Box& page);

  private:
    Controller& controller;
    FileGroup& filegroup;
    Gtk::Box& page;
    ConfigTable entrytable {};
    ConfigTable filetable {};

    void on_add_entry ();
    void on_add_file ();
    void on_type_changed ();

    Gtk::HBox radiobox {};
    Gtk::RadioButton databutton;
    Gtk::RadioButtonGroup radiogroup;
    Gtk::RadioButton mcbutton;
    Gtk::RadioButton signalbutton;

    Gtk::VBox legendlist {};
    Gtk::VBox filelist {};
    Gtk::HButtonBox addlegendbox {};
    Gtk::HButtonBox addfilebox {};
    Gtk::Button addentrybutton {"Add File"};
    Gtk::Button addfilebutton {"Add File"};

  };
}


#endif
