#include <crombie2/BoolConfigurable.h>


using namespace crombie2;


BoolConfigurable::BoolConfigurable (const std::string& label) :
  name {label}
{

  checkbox.signal_toggled().connect(sigc::mem_fun(*this, &BoolConfigurable::on_update));

}


std::string BoolConfigurable::label () const {

  return name;

}


std::string BoolConfigurable::get () const {

  return value ? "1" : "0";

}


void BoolConfigurable::set (const std::string& input) {

  value = (input.size() and (input != "0"));
  checkbox.set_active(value);

}


Gtk::Widget& BoolConfigurable::get_widget () {

  return checkbox;

}


BoolConfigurable::operator bool () const {

  return value;

}


void BoolConfigurable::on_update () {

  value = checkbox.get_active();

}
