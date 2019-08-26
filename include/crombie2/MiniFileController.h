#ifndef CROMBIE2_MINIFILECONTROLLER_H
#define CROMBIE2_MINIFILECONTROLLER_H


#include <gtkmm/buttonbox.h>
#include <gtkmm/radiobutton.h>

#include <crombie2/FileGroup.h>


namespace crombie2 {
  /**
     @brief Handles each the GUI interactions for a single FileGroup
  */
  class MiniFileController {
  public:
    MiniFileController(RemoveWrapper<FileGroup>& filegroup, Gtk::Box& page);

  private:
    FileGroup& filegroup;
    ConfigTable entrytable {};
    ConfigTable filetable {};

    void on_add_entry ();
    void on_add_file ();
    void on_type_changed ();

    Gtk::Frame frame {};
    Gtk::VBox inframe {};

    Gtk::HBox radiobox {};
    Gtk::RadioButton databutton;
    Gtk::RadioButtonGroup radiogroup;
    Gtk::RadioButton mcbutton;
    Gtk::RadioButton signalbutton;

    Gtk::VBox legendlist {};
    Gtk::VBox filelist {};
    Gtk::HButtonBox addlegendbox {};
    Gtk::HButtonBox addfilebox {};
    Gtk::HButtonBox removebox {};
    Gtk::Button addentrybutton {"Add Entry"};
    Gtk::Button addfilebutton {"Add File"};

    void setup_radio (Gtk::RadioButton& button, FileGroup::FileType type);

  };
}


#endif
