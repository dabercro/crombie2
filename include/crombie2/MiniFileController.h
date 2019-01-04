#ifndef CROMBIE2_MINIFILECONTROLLER_H
#define CROMBIE2_MINIFILECONTROLLER_H


#include <crombie2/FileGroup.h>


namespace crombie2 {
  class MiniFileController {
  public:
    MiniFileController(Controller& controller, FileGroup& filegroup);

    void draw (Gtk::Box& page);

  private:
    Controller& controller;
    FileGroup& filegroup;
    ConfigTable<> entrytable {};
    ConfigTable<> filetable {};

    void on_add_entry ();
    void on_add_file ();

    Gtk::HBox box {};
    Gtk::VBox filelist {};
    Gtk::Button addentrybutton {"Add File"};
    Gtk::Button addfilebutton {"Add File"};

  };
}


#endif
