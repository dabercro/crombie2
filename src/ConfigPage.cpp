#include <crombie2/ConfigPage.h>

using namespace crombie2;

ConfigPage::ConfigPage (const std::string& label) :
  label {label} {

  add(updatebox);
  updatebox.show();

}

const std::string& ConfigPage::get_label () {
  return label;
}
