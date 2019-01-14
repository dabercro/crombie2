#include <crombie2/MiniFileController.h>


using namespace crombie2;


MiniFileController::MiniFileController(Controller& controller, FileGroup& filegroup, Gtk::Box& page) :
  controller {controller},
  filegroup {filegroup},
  databutton {"DATA"},
  radiogroup {databutton.get_group()},
  mcbutton {radiogroup, "MC"},
  signalbutton {radiogroup, "SIGNAL"}
{

  page.pack_start(frame, Gtk::PACK_SHRINK);
  frame.add(inframe);

  frame.show();
  inframe.show();

  auto fill = [&] (auto& confs, auto& box, auto& button, auto& buttonbox, auto func) {
    inframe.pack_start(box, Gtk::PACK_SHRINK);
    box.show();

    if (not confs.size())
      confs.emplace_back();

    for (auto& entry : confs)
      entry.table.draw(controller, box);

    button.set_border_width(10);

    box.pack_end(buttonbox);
    buttonbox.pack_start(button, Gtk::PACK_SHRINK);

    buttonbox.show();
    button.show();

    button.signal_clicked().
      connect(sigc::mem_fun(*this, func));
  };

  inframe.pack_start(radiobox, Gtk::PACK_SHRINK);

  radiobox.show();

  setup_radio(databutton, FileGroup::FileType::DATA);
  setup_radio(mcbutton, FileGroup::FileType::MC);
  setup_radio(signalbutton, FileGroup::FileType::SIGNAL);

  fill(filegroup.entries, legendlist, addentrybutton, addlegendbox, &MiniFileController::on_add_entry);
  fill(filegroup.files, filelist, addfilebutton, addfilebox, &MiniFileController::on_add_file);

}


void MiniFileController::on_add_entry () {

  filegroup.entries.emplace_back().table.draw(controller, legendlist);

}


void MiniFileController::on_add_file () {

  filegroup.files.emplace_back().table.draw(controller, filelist);

}


void MiniFileController::on_type_changed () {

  if (databutton.get_active())
    filegroup.type = FileGroup::FileType::DATA;
  else if (mcbutton.get_active())
    filegroup.type = FileGroup::FileType::MC;
  else if (signalbutton.get_active())
    filegroup.type = FileGroup::FileType::SIGNAL;

}


void MiniFileController::setup_radio (Gtk::RadioButton& button, FileGroup::FileType type) {

  radiobox.pack_start(button);
  button.show();

  if (type == filegroup.type)
    button.set_active();

  button.signal_clicked().
    connect(sigc::mem_fun(*this, &MiniFileController::on_type_changed));

}
