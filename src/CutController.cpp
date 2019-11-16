#include <crombie2/CutController.h>


using namespace crombie2;


CutController::CutController (ConfigPage& page, CutModel& model) :
  CutsController<CutModel> {page, model}
{

  buttonbox.pack_start(addselectionbutton, Gtk::PACK_SHRINK);
  addselectionbutton.set_border_width(10);
  addselectionbutton.show();

  addselectionbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &CutController::on_add_selection));

  page.box().pack_end(selectionbox, Gtk::PACK_SHRINK);
  selectionbox.show();

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


void CutController::on_add_selection () {

  fill_selection(cutmodel.selections.
                 emplace_back(cutmodel.selections)); // RemoveWrapper needs a reference to this list

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
