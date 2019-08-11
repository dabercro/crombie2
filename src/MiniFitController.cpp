#include <crombie2/MiniFitController.h>


using namespace crombie2;


MiniFitController::MiniFitController (RemoveWrapper<FitConfig>& fit) :
  fit {fit},
  functiontable {&fit}
{

  for (auto& guess : fit.guesses)
    parametertable.add_conf(&guess);

}



void MiniFitController::draw (Gtk::Box& page) {

  page.pack_start(fit.remove, Gtk::PACK_SHRINK);
  fit.remove.show();

  page.pack_start(box, Gtk::PACK_SHRINK);

  functiontable.draw(functionlist);
  parametertable.draw(guesslist);

  box.pack_start(functionlist, Gtk::PACK_SHRINK);
  box.pack_start(guesslist, Gtk::PACK_SHRINK);
  functionlist.pack_end(updatebutton, Gtk::PACK_SHRINK);
  updatebutton.set_border_width(10);

  box.show();
  functionlist.show();
  guesslist.show();
  updatebutton.show();

  updatebutton.signal_clicked().
    connect(sigc::mem_fun(*this, &MiniFitController::on_update_fit));

}


void MiniFitController::on_update_fit () {

  fit.resize_guesses();

  parametertable.clear();

  for (auto& guess : fit.guesses)
    parametertable.add_conf(&guess);

  parametertable.redraw();

}
