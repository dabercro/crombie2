#include <crombie2/MiniFileController.h>


using namespace crombie2;


MiniFileController::MiniFileController(Controller& controller, FileGroup& filegroup, Gtk::Box& page) :
  controller {controller},
  filegroup {filegroup},
  page {page}
{

  auto fill = [&] (auto& confs, auto& box) {
    page.pack_start(box, Gtk::PACK_SHRINK);
    box.show();

    if (not confs.size())
      confs.emplace_back();

    for (auto& entry : confs)
      entry.table.draw(controller, box);
  };

  fill(filegroup.entries, legendlist);
  fill(filegroup.files, filelist);

}


void MiniFileController::on_add_entry () {

}


void MiniFileController::on_add_file () {

}
