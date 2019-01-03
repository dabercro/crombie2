#include <crombie2/ConfigRef.h>


using namespace crombie2;


ConfigRef::ConfigRef (GuiConfigurable& config, const std::string& label) :
  config {config}, label {label, Gtk::ALIGN_START} {}


void ConfigRef::show () {

  box.show();
  label.show();
  entry.show();

}
