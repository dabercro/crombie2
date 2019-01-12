#include <crombie2/TextConfigurable.h>


using namespace crombie2;


TextConfigurable::TextConfigurable () {

  entry.signal_changed().connect(sigc::mem_fun(*this, &TextConfigurable::on_update));

}

TextConfigurable::TextConfigurable (const TextConfigurable& other) :
  TextConfigurable() {}


Gtk::Widget& TextConfigurable::get_widget () {

  entry.set_text(get());
  return entry;

}


void TextConfigurable::on_update () {

  set(entry.get_chars(0, -1));

}
