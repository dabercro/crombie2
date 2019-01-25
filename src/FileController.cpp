#include <crombie2/Error.h>
#include <crombie2/FileController.h>
#include <crombie2/Misc.h>


using namespace crombie2;


FileController::FileController (ConfigPage& page, FileModel& model) :
  Controller {page, model},
  filemodel {model}
{

  buttonbox.pack_start(addbutton, Gtk::PACK_SHRINK);
  addbutton.set_border_width(10);

  buttonbox.pack_start(checkxs, Gtk::PACK_SHRINK);
  checkxs.set_border_width(10);

  page.pack_start(buttonbox, Gtk::PACK_SHRINK);

  buttonbox.show();
  addbutton.show();
  checkxs.show();

  addbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &FileController::on_add_group));

  checkxs.signal_clicked().
    connect(sigc::mem_fun(*this, &FileController::on_check_xs));

  page.box().pack_end(crosssecbox, Gtk::PACK_SHRINK);
  crosssecbox.show();
  xs_db.load_tag(Controller::last_tag);
  xs_db.configs.draw(crosssecbox);

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


void FileController::on_check_xs () {

  xs_db.save_tag(Controller::last_tag);

  if (xs_db.executable.get().size()) {

    for (auto& group : filemodel.filegroups) {
      if (group.type == FileGroup::FileType::DATA)
        continue;

      for (auto& file : group.files) {
        auto dataset = Misc::split(file.name, "/").back();
        auto xs = xs_db.get_xs(dataset);

        if (xs != file.xs and
            Misc::confirm(std::string("Change ") + file.name.get() + "?\n" +
                          file.xs.get() + " -> " + std::to_string(xs)))
          file.xs = xs;
      }
    }
  }
  else
    Error::Exception("Cross Section Getter is not set!");

}
