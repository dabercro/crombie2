#ifndef CROMBIE2_FILECONTROLLER_H
#define CROMBIE2_FILECONTROLLER_H


#include <gtkmm/buttonbox.h>

#include <crombie2/FileModel.h>


namespace crombie2 {
  class FileController : public Controller {

  public:
    FileController (ConfigPage& page, FileModel& model);

  protected:
    void redraw () override;

  private:
    void on_add_group ();

    FileModel& filemodel;

    std::list<Gtk::HBox> boxes {};
    Gtk::HButtonBox buttonbox {};
    Gtk::Button addbutton {"Add File Group"};

  };
}


#endif
