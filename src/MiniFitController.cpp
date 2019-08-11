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

  updatebutton.signal_clicked().
    connect(sigc::mem_fun(*this, &MiniFitController::on_update_fit));

}
