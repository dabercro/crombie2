#include <crombie2/DatacardController.h>


using namespace crombie2;


DatacardController::DatacardController (ConfigPage& page, DatacardModel& model) :
  Controller {page, model},
  datacardmodel {model},
  info {&model.outdir}
{

  info.draw(page.box());

  page.draw(plotlabel);

  for (auto& hist : datacardmodel.hists)
    draw_config(hist, plots);

  page.draw(plots);
  page.draw(plotbutton);

  for (auto& flat : datacardmodel.flats)
    draw_config(flat, uncertainties);

  page.draw(uncertainties);
  page.draw(uncbutton);

  plotbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &DatacardController::on_add_plot));
  uncbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &DatacardController::on_add_unc));

}


void DatacardController::redraw () {

  plotboxes.clear();

  for (auto& conf : datacardmodel.hists)
    draw_config(conf, plots);

  for (auto& conf : datacardmodel.flats)
    draw_config(conf, uncertainties);

}


void DatacardController::on_add_plot () {

  draw_config(datacardmodel.hists.append(), plots);

}


void DatacardController::on_add_unc () {

  draw_config(datacardmodel.flats.append(), uncertainties);

}
