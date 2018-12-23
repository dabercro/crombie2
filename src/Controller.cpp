#include <exception>

#include <crombie2/Controller.h>


using namespace crombie2;


Controller::ConfigRef::ConfigRef (GuiConfigurable& config, const std::string& label) :
  config {config}, label {label, Gtk::ALIGN_START} {}


void Controller::ConfigRef::show () {

  box.show();
  label.show();
  entry.show();

}


Controller::Controller (ConfigPage& page, ConfigModel& model) :
  page {page},
  model {model}
{}


ConfigPage& Controller::get_page () {
  return page;
}


void Controller::add_update () {

  updatebox.update().signal_clicked().
    connect(sigc::mem_fun(*this, &Controller::on_update));

  page.add(updatebox);
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
