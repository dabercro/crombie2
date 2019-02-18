#include <exception>

#include <crombie2/Controller.h>


using namespace crombie2;


ConfigPage::ConfigPage (const std::string& label) :
  label {label}
{
  set_border_width(10);

  add(scrolled);
  scrolled.show();
  scrolled.add(internalbox);

  internalbox.set_border_width(15);
  internalbox.show();
}


ConfigPage& ConfigPage::operator=(const ConfigPage& other) {

  label = other.label;
  return *this;

}


const std::string& ConfigPage::get_label () {
  return label;
}


Gtk::VBox& ConfigPage::box () {
  return internalbox;
}


void ConfigPage::set_controller_model (Controller& controller, ConfigModel& model) {

  controller_ptr = &controller;
  model_ptr = &model;

}


Controller& ConfigPage::get_controller () {

  if (controller_ptr)
    return *controller_ptr;

  throw std::logic_error {"ConfigPage::get_controller: Controller not set yet"};

}


ConfigModel& ConfigPage::get_model () {

  if (model_ptr)
    return *model_ptr;

  throw std::logic_error {"ConfigPage::get_model: Model not set yet"};

}
