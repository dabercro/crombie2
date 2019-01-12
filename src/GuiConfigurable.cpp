#include <crombie2/GuiConfigurable.h>


using namespace crombie2;


Gtk::Label& GuiConfigurable::get_label () {

  label_obj.set_text(label());
  return label_obj;

}
