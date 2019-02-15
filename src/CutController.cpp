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

  page.box().pack_end(selectionbox, Gtk::PACK_SHRINK);
  selectionbox.show();

  // Draws the stuff loaded by the Controller constructor
  redraw();

}


void CutController::redraw () {

  numcuts = 0;
  selectiondisplays.clear();
  cutboxes.clear();
  minicontrollers.clear();

  for (auto& cut : cutmodel.get_labels())
    add_cut(cutmodel.get_cutstring(cut));

  for (auto& selection : cutmodel.selections)
    fill_selection(selection);

}


void CutController::add_cut (CutString& cutstring) {

  if (((numcuts++) % 1) == 0) {
    cutboxes.emplace_back();
    page.box().pack_start(cutboxes.back(), Gtk::PACK_SHRINK);
    cutboxes.back().show();
  }

  minicontrollers.emplace_back(cutstring);
  minicontrollers.back().draw(cutboxes.back());

}


void CutController::on_add_cut () {

  add_cut(cutmodel.add_cutstring(labelentry.get_chars(0, -1)));

}


void CutController::on_add_selection () {

  fill_selection(cutmodel.selections.
                 emplace_back(cutmodel.selections, // RemoveWrapper needs a reference to this list
                              "", "", ""));        // Otherwise, fill with empty space

}


void CutController::fill_selection (RemoveWrapper<Selection>& selection) {

  auto& display = selectiondisplays.emplace_back(cutmodel, selection);

  selectionbox.pack_start(display.box, Gtk::PACK_SHRINK);

  selection.table.draw(display.box);
  display.box.pack_end(display);

  selection.also_remove([&display, this] () {
      selectiondisplays.remove_if([&display] (auto& ele) { return &ele == &display; });
    });

  display.box.pack_start(selection.remove, Gtk::PACK_SHRINK);
  selection.remove.show();

  display.box.show();
  display.show();

}
