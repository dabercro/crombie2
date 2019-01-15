#include <crombie2/FileController.h>


using namespace crombie2;


FileController::FileController (ConfigPage& page, FileModel& model) :
  Controller {page, model},
  filemodel {model}
{

  buttonbox.pack_start(addbutton, Gtk::PACK_SHRINK);
  addbutton.set_border_width(10);

  page.pack_start(buttonbox, Gtk::PACK_SHRINK);

  buttonbox.show();
  addbutton.show();

  addbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &FileController::on_add_group));

  redraw();

}


void FileController::redraw () {

  minicontrollers.clear();

  for (auto& group : filemodel.filegroups)
    minicontrollers.emplace_back(group, page.box());

}


void FileController::on_add_group () {

  minicontrollers.emplace_back(filemodel.add_files(), page.box());

}
