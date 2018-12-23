#include <crombie2/ConfigPage.h>


using namespace crombie2;


ConfigPage::ConfigPage (const std::string& label) :
  label {label} {
  add(scrolled);
  scrolled.show();
  scrolled.add(internalbox);
  internalbox.show();
}


const std::string& ConfigPage::get_label () {
  return label;
}


Gtk::VBox& ConfigPage::box () {
  return internalbox;
}
