#include <crombie2/UpdateBox.h>

using namespace crombie2;

UpdateBox::UpdateBox () {

  pack_start(updatebutton, Gtk::PACK_EXPAND_PADDING);
  updatebutton.show();

}
