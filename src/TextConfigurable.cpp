#include <crombie2/TextConfigurable.h>


using namespace crombie2;


TextConfigurable::TextConfigurable (const std::string& tooltip) :
  GuiConfigurable {tooltip}
{

  if (tooltip.size())
    entry.set_tooltip_text(tooltip);

  entry.signal_changed().connect(sigc::mem_fun(*this, &TextConfigurable::on_update));

}

TextConfigurable::TextConfigurable (const TextConfigurable& other) :
  TextConfigurable {other.label_obj.get_tooltip_text()} {}


Gtk::Widget& TextConfigurable::get_widget () {

  entry.set_text(get());
  return entry;

}


void TextConfigurable::on_update () {

  set(entry.get_chars(0, -1));

}
