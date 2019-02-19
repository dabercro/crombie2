#include <crombie2/MiniCutController.h>


using namespace crombie2;


MiniCutController::MiniCutController(RemoveWrapper<CutString>& cutstring) :
  cutstring {cutstring},
  labeltable{&(cutstring.name), &(cutstring.joiner)},
  cuttable {}
{

  auto& cuts = cutstring.get_cuts();

  if (not cuts.size())
    cutstring.add_cut();

  for (auto& cut : cuts)
    cuttable.add_conf(&cut);

}


void MiniCutController::draw (Gtk::Box& page) {

  page.pack_start(cutstring.remove, Gtk::PACK_SHRINK);
  cutstring.remove.show();

  page.pack_start(box, Gtk::PACK_SHRINK);

  labeltable.draw(labellist);
  cuttable.draw(cutlist);

  box.pack_start(labellist, Gtk::PACK_SHRINK);
  box.pack_start(cutlist, Gtk::PACK_SHRINK);
  cutlist.pack_end(addbutton, Gtk::PACK_SHRINK);
  addbutton.set_border_width(10);

  box.show();
  labellist.show();
  cutlist.show();
  addbutton.show();

  addbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &MiniCutController::on_add_cut));

}


void MiniCutController::on_add_cut () {

  auto& cut = cutstring.add_cut();

  cuttable.add_conf(&cut);
  cuttable.redraw();

}
