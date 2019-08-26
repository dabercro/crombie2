#ifndef CROMBIE2_FILECONTROLLER_H
#define CROMBIE2_FILECONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/CrossSecDB.h>
#include <crombie2/FileModel.h>
#include <crombie2/MiniFileController.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the FileModel
  */
  class FileController : public Controller {

  public:
    FileController (ConfigPage& page, FileModel& model);

    void redraw () override;

  private:
    void on_add_group ();

    FileModel& filemodel;

    Gtk::HButtonBox buttonbox {};
    Gtk::Button addbutton {"Add File Group"};

    std::list<MiniFileController> minicontrollers {};

    Gtk::HBox crosssecbox {};

    CrossSecDB xs_db {};

    void on_check_xs ();
    Gtk::Button checkxs {"Check Cross Sections"};

  };
}


#endif
