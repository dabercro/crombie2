#include <exception>

#include <crombie2/Controller.h>


using namespace crombie2;


Controller::Controller (ConfigPage& page, ConfigModel& model) :
  page {page},
  model {model}
{

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
  model.save_tag(tagentry.get_chars(0, -1));

}


void Controller::on_load () {

  model.load_tag(tagentry.get_chars(0, -1));
  redraw();
  on_update();

}
