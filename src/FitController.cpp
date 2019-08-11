#include <crombie2/FitController.h>


using namespace crombie2;


FitController::FitController (ConfigPage& page, FitModel& model) :
  Controller {page, model},
  fitmodel {model}
{

  buttonbox.pack_start(fitentry, Gtk::PACK_SHRINK);
  buttonbox.pack_start(addfitbutton, Gtk::PACK_SHRINK);

  addfitbutton.set_border_width(10);

  fitentry.show();
  addfitbutton.show();
  buttonbox.show();

  page.pack_start(buttonbox, Gtk::PACK_SHRINK);

  addfitbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &FitController::on_add_fit));

  // Draws the stuff loaded by the Controller constructor
  redraw();

}


void FitController::redraw () {

  numfits = 0;
  fitboxes.clear();
  minicontrollers.clear();

  for (auto& fit : fitmodel.fits)
    add_fit(fit);

}


void FitController::add_fit (RemoveWrapper<FitConfig>& fit) {

  if (((numfits++) % 1) == 0)
    page.draw(fitboxes.emplace_back());

  auto& mini = minicontrollers.emplace_back(fit);
  mini.draw(fitboxes.back());

  fit.also_remove([&mini, this] () {
      minicontrollers.remove_if([&mini] (auto& ele) {
          return &mini == &ele;
        });
    });

}


void FitController::on_add_fit () {

  add_fit(fitmodel.fits.append(fitentry.get_chars(0, -1)));

}
