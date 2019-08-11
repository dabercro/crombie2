#include <crombie2/ConfigTable.h>
#include <crombie2/Misc.h>


using namespace crombie2;


ConfigTable::ConfigTable (const std::initializer_list<GuiConfigurable*>& configs, const bool horizontal) :
  confs {configs},
  table {horizontal ? 1 : size(), horizontal ? 2 * size() : 2},
  horizontal {horizontal}
{

  table.set_spacings(10);
  if (not horizontal) {
    table.set_border_width(20);
    frame.add(table);
  }

}


void ConfigTable::copy (const ConfigTable& other) {

  auto iter = other.get_confs().begin();
  for (auto* configurable : get_confs())
    configurable->set((*iter++)->get());

}


const std::vector<GuiConfigurable*>& ConfigTable::get_confs () const {

  return confs;

}


void ConfigTable::draw (Gtk::Box& page) {

  if (horizontal)
    page.pack_start(table, Gtk::PACK_SHRINK);
  else {
    page.pack_start(frame, Gtk::PACK_SHRINK);
    frame.show();
  }

  redraw();

}


void ConfigTable::redraw () {

  for (auto* child : table.get_children())
    table.remove(*child);

  table.resize(horizontal ? 1 : size(), horizontal ? 2 * size() : 2);

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

  table.show();

}


void ConfigTable::add_conf (GuiConfigurable* conf) {

  confs.push_back(conf);

}


guint ConfigTable::size () const {

  return static_cast<guint>(std::max(confs.size(), 1ul));

}


std::string ConfigTable::dump () const {

  std::string output {};

  for (auto* conf : confs) {
    auto conf_str = conf->get();

    if (not conf_str.size())
      conf_str = "_";

    output += conf_str + ' ';
  }

  output.pop_back();

  return output;

}


void ConfigTable::fill (const std::string& line) const {

  unsigned index {0};

  for (auto& val : Misc::tokenize(line))
    confs.at(index++)->set(val == "_" ? "" : val);

}


void ConfigTable::clear () {

  confs.clear();
  redraw();

}
