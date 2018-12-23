#include <crombie2/UpdateBox.h>


using namespace crombie2;


UpdateBox::UpdateBox () {

  updatebutton.set_border_width(10);
  pack_start(updatebutton, Gtk::PACK_EXPAND_PADDING);
  updatebutton.show();

}


Gtk::Button& UpdateBox::update () {
  return updatebutton;
}
