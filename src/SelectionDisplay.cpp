#include <sstream>

#include <gtkmm/messagedialog.h>

#include <crombie2/SelectionDisplay.h>


using namespace crombie2;


SelectionDisplay::SelectionDisplay (CutModel& cutmodel, Selection& selection) :
  Gtk::Button {"Show Cutstring"},
  model {cutmodel},
  selection {selection}
{

  signal_clicked().connect(sigc::mem_fun(*this, &SelectionDisplay::on_click));

}


void SelectionDisplay::on_click () {

  Gtk::MessageDialog message (selection.get_name());

  std::stringstream ss {};

  ss << "Cut:" << std::endl
     << model.expand(selection.cut)
     << std::endl << std::endl
     << "Data Weight:" << std::endl
     << model.expand(selection.data_weight)
     << std::endl << std::endl
     << "MC Weight:" << std::endl
     << model.expand(selection.mc_weight);

  message.set_secondary_text(ss.str());

  message.run();

}
