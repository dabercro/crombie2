#include <exception>

#include <crombie2/Controller.h>


using namespace crombie2;


Controller::ConfigRef::ConfigRef (GuiConfigurable& config, const std::string& label) :
  config {config}, label {label, Gtk::ALIGN_TOP} {}


void Controller::ConfigRef::show () {

  box.show();
  label.show();
  entry.show();

}


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


Controller::ConfigRef& Controller::register_configurable (GuiConfigurable& config) {

  configurables.emplace_back(config, config.label());
  return configurables.back();

}


void Controller::register_configurable (GuiConfigurable& config, Gtk::Box& box) {

  auto& todraw = register_configurable(config);

  box.pack_start(todraw.box);

  todraw.box.pack_start(todraw.label);
  todraw.box.pack_start(todraw.entry);

  todraw.entry.set_text(config.get());

  todraw.show();

}


void Controller::unregister_configurable (GuiConfigurable& config) {

  auto iter = configurables.begin();

  while (iter != configurables.end()) {
    if (&config == &(iter->config)) {
      configurables.erase(iter);
      return;
    }
  }

  throw std::logic_error{"Asked to remove a configurable that doesn't seem to exist"};

}


const std::string Controller::last_tag = "latest";


void Controller::on_update () {

  for (auto& configref : configurables) {
    configref.config.set(configref.entry.get_chars(0, -1));
    configref.entry.set_text(configref.config.get());
  }

  model.save_tag(last_tag);

}


void Controller::on_save () {

  on_update();
  model.save_tag(tagentry.get_chars(0, -1));

}


void Controller::on_load () {

  model.load_tag(tagentry.get_chars(0, -1));
  configurables.clear();
  redraw();
  on_update();

}
