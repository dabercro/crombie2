#include <exception>

#include <crombie2/Controller.h>
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

  for (auto* button : {&loadbutton, &savebutton, &updatebutton}) {
    button->set_border_width(5);
    updatebox.pack_end(*button, Gtk::PACK_SHRINK);
    button->show();
  }

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

  model.save_tag(last_tag);

}


void Controller::on_save () {

  on_update();
  model.save_tag(tagentry.get_entry()->get_text());
  update_entries();

}


void Controller::on_load () {

  model.load_tag(tagentry.get_active_text());
  redraw();
  on_update();

}


void Controller::update_entries () {

  tagentry.clear_items();

  for (auto& file :
         FileSystem::list(ConfigModel::get_config_dir() + "/" + model.get_name() + "/tags"))
    if (file != last_tag)
      tagentry.append_text(file);

}
