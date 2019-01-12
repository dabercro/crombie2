#include <crombie2/ConfigTable.h>


using namespace crombie2;


ConfigTable::ConfigTable (const std::initializer_list<GuiConfigurable*>& configs, const bool horizontal) :
  confs {configs},
  table {horizontal ? 1 : size(), horizontal ? 2 * size() : 2},
  horizontal {horizontal}
{

  table.set_spacings(10);

}


const std::vector<GuiConfigurable*>& ConfigTable::get_confs () const {

  return confs;

}


void ConfigTable::draw (Controller& control, Gtk::Box& page) {

  page.pack_start(table, Gtk::PACK_SHRINK);
  table.show();

  redraw(control);

}


void ConfigTable::redraw (Controller& control) {

  table.hide_all();

  for (auto* child : table.get_children())
    table.remove(*child);

  table.resize(horizontal ? 1 : size(), horizontal ? 2 * size() : 2);
  table.show();

  for (unsigned i_conf = 0; i_conf != confs.size(); i_conf++) {
    auto* config = confs[i_conf];

    guint col = horizontal ? i_conf * 2 : 0;
    guint row = horizontal ? 0 : i_conf;

    auto& label = config->get_label();
    auto& entry = config->get_widget();

    table.attach(label, col, col + 1, row, row + 1);
    table.attach(entry, col + 1, col + 2, row, row + 1);
    label.show();
    entry.show();
  }

}


void ConfigTable::add_conf (GuiConfigurable* conf) {

  confs.push_back(conf);

}


guint ConfigTable::size () const {

  return static_cast<guint>(std::max(confs.size(), 1ul));

}
