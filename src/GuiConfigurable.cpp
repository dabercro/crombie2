#include <crombie2/GuiConfigurable.h>


using namespace crombie2;

GuiConfigurable::GuiConfigurable () {

  label_obj.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);

}

Gtk::Label& GuiConfigurable::get_label () {

  label_obj.set_text(label());
  return label_obj;

}
