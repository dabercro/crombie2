#include <gtkmm/filechooserdialog.h>

#include <crombie2/Controller.h>
#include <crombie2/Error.h>
#include <crombie2/FileSystem.h>


using namespace crombie2;


Controller::Controller (ConfigPage& page, ConfigModel& model) :
  page {page},
  model {model}
{

  update_entries();

  model.load_tag(last_tag);

  updatebox.pack_end(tagentry, Gtk::PACK_SHRINK);
  tagentry.show();

  for (auto* button : {&loadbutton, &savebutton,
        &exportbutton, &importbutton, &updatebutton}) {

    button->set_border_width(5);
    updatebox.pack_end(*button, Gtk::PACK_SHRINK);
    button->show();

  }

  exportbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &Controller::on_export));
  importbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &Controller::on_import));

  updatebutton.signal_clicked().
    connect(sigc::mem_fun(*this, &Controller::on_update));
  savebutton.signal_clicked().
    connect(sigc::mem_fun(*this, &Controller::on_save));
  loadbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &Controller::on_load));

  page.pack_end(updatebox, Gtk::PACK_SHRINK);
  updatebox.show();

}


const std::string Controller::last_tag = "latest";


void Controller::on_update () {

  model.save_tag(last_tag, true);

}


void Controller::on_save () {

  on_update();
  auto text = tagentry.get_entry()->get_text();
  model.save_tag(text);
  update_entries();
  tagentry.set_active_text(text);

}


void Controller::on_load () {

  model.load_tag(tagentry.get_active_text());
  redraw();
  on_update();

}


void Controller::on_export () {

  // Uses the tag entry widget for file name
  auto filename = tagentry.get_entry()->get_text();
  if (not filename.size())
    Error::Exception("No target file", "Enter the file name into the tag entry");
  else
    if (FileSystem::confirm_overwrite(filename))
      model.save(filename);

}


void Controller::on_import () {

  Gtk::FileChooserDialog dialog {model.get_name() + ": Choose a configuration file"};
  dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("Open", Gtk::RESPONSE_OK);

  if (dialog.run() == Gtk::RESPONSE_OK) {
    auto filename = dialog.get_filename();
    try {
      model.load(filename);
    }
    catch (const std::exception& e) {
      Error::Exception (e, filename + " doesn't seem to be a valid file.");
      model.load_tag(last_tag);
    }
  }
  redraw();

}


void Controller::update_entries () {

  tagentry.clear_items();

  for (auto& file :
         FileSystem::list(ConfigModel::get_config_dir() + "/" + model.get_name() + "/tags",
                          false))  // The tag directory might not exist (e.g., for a new user)
    tagentry.append_text(file);

}
