#include <crombie2/ConfigTable.h>


using namespace crombie2;


ConfigTable::ConfigTable (const std::initializer_list<GuiConfigurable*>& configs) :
  confs {configs},
  table {static_cast<guint>(configs.size()), 2} {}


const std::vector<GuiConfigurable*>& ConfigTable::get_confs () const {
  return confs;
}


void ConfigTable::draw (Controller& controller, Gtk::Box& page) {

  page.pack_start(box, Gtk::PACK_SHRINK);
  box.pack_start(table, Gtk::PACK_SHRINK);
  box.show();
  table.show();

  for (unsigned row = 0; row != confs.size(); row++) {
    auto* config = confs[row];
    auto& info = controller.register_configurable(*config);
    table.attach(info.label, 0, 1, row, row + 1);
    table.attach(info.entry, 1, 2, row, row + 1);
    info.entry.set_text(info.config.get());
    info.label.show();
    info.entry.show();
  }

}
