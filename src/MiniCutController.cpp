#include <crombie2/MiniCutController.h>


using namespace crombie2;


MiniCutController::MiniCutController(Controller& controller, CutString& cutstring) :
  controller {controller}, cutstring {cutstring},
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

  page.pack_start(box, Gtk::PACK_SHRINK);

  labeltable.draw(controller, box);
  cuttable.draw(controller, cutlist);

  box.pack_start(cutlist, Gtk::PACK_SHRINK);
  cutlist.pack_end(addbutton, Gtk::PACK_SHRINK);
  addbutton.set_border_width(10);

  box.show();
  cutlist.show();
  addbutton.show();

}
