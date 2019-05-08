#include <exception>

#include <gtkmm/scrollbar.h>

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


void ConfigPage::scroll (Scroll direction) {

  auto bar = (direction == Scroll::DOWN or direction == Scroll::UP)
    ? std::make_pair(static_cast<Gtk::Scrollbar*> (scrolled.get_vscrollbar()), scrolled.get_vadjustment())
    : std::make_pair(static_cast<Gtk::Scrollbar*> (scrolled.get_hscrollbar()), scrolled.get_hadjustment());

  auto location = bar.first->get_value();
  auto step = bar.second->get_step_increment() * (direction == Scroll::DOWN or
                                                  direction == Scroll::RIGHT
                                                  ? 1.0 : -1.0);

  bar.first->set_value(location + step);

}


void ConfigPage::draw (Gtk::Widget& widget) {

  internalbox.pack_start(widget, Gtk::PACK_SHRINK);
  widget.show();

}
