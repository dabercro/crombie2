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

  auto label = selection.cut.get();
  auto output = model.expand(label);

  Gtk::MessageDialog message (label);
  message.set_secondary_text(output);

  message.run();

}
