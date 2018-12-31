#include <crombie2/CutController.h>

using namespace crombie2;

CutController::CutController (ConfigPage& page, CutModel& model) :
  Controller {page, model},
  cutmodel {model}
{

  buttonbox.pack_start(labelentry, Gtk::PACK_SHRINK);
  buttonbox.pack_start(addcutbutton, Gtk::PACK_SHRINK);
  buttonbox.pack_start(addselectionbutton, Gtk::PACK_SHRINK);

  addcutbutton.set_border_width(10);
  addselectionbutton.set_border_width(10);

  labelentry.show();
  addcutbutton.show();
  addselectionbutton.show();
  buttonbox.show();

  page.pack_start(buttonbox, Gtk::PACK_SHRINK);

  addcutbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &CutController::on_add_cut));
  addselectionbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &CutController::on_add_selection));

  page.pack_end(selectionbox, Gtk::PACK_SHRINK);

  // Draws the stuff loaded by the Controller constructor
  redraw();

}


void CutController::redraw () {

  numcuts = 0;
  cutboxes.clear();

  for (auto& cut : cutmodel.get_labels())
    add_cut(cutmodel.get_cutstring(cut));

  for (auto& selection : cutmodel.selections)
    selection.table.redraw(*this);

}


void CutController::add_cut (CutString& cutstring) {

  if (((numcuts++) % 3) == 0) {
    cutboxes.emplace_back();
    page.box().pack_start(cutboxes.back(), Gtk::PACK_SHRINK);
    cutboxes.back().show();
  }

  minicontrollers.emplace_back(*this, cutstring);
  minicontrollers.back().draw(cutboxes.back());

}


void CutController::on_add_cut () {

  add_cut(cutmodel.add_cutstring(labelentry.get_chars(0, -1)));

}


void CutController::on_add_selection () {

}
