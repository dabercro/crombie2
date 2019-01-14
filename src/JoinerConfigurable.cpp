#include <crombie2/JoinerConfigurable.h>


using namespace crombie2;


JoinerConfigurable::JoinerConfigurable (const std::string& value) :
  value {value}
{

  combobox.append_text("&&");
  combobox.append_text("||");
  combobox.append_text("*");

  combobox.set_active_text(value);

  combobox.signal_changed().
    connect(sigc::mem_fun(*this, &JoinerConfigurable::on_update));

}


JoinerConfigurable::JoinerConfigurable (const JoinerConfigurable& other) :
  JoinerConfigurable {other.get()} {}


std::string JoinerConfigurable::label () const {

  return "Join with";

}


std::string JoinerConfigurable::get () const {

  return value;

}


void JoinerConfigurable::set (const std::string& input) {

  value = input;

}


Gtk::Widget& JoinerConfigurable::get_widget () {

  return combobox;

}


void JoinerConfigurable::on_update () {

  set(combobox.get_active_text());

}
