#include <crombie2/DatacardController.h>


using namespace crombie2;


DatacardController::DatacardController (ConfigPage& page, DatacardModel& model) :
  Controller {page, model},
  datacardmodel {model},
  info {&model.outdir}
{

  info.draw(page.box());

  auto renderlist = [&page, this] (auto& label, auto& list, auto& vbox,
                                   auto& button, auto target) {

    page.draw(label);

    for (auto& ele : list)
      draw_config(ele, vbox);

    page.draw(vbox);
    page.draw(button);

    button.signal_clicked().
      connect(sigc::mem_fun(*this, target));

  };

  // Plots for datacard

  renderlist(plotlabel, datacardmodel.hists, plots,
             plotbutton, &DatacardController::on_add_plot);

  // Uncertainties

  renderlist(unclabel, datacardmodel.flats, uncertainties,
             uncbutton, &DatacardController::on_add_unc);

  // RateParams

  renderlist(ratelabel, datacardmodel.rateparams, rateparams,
             ratebutton, &DatacardController::on_add_rate);

}


void DatacardController::redraw () {

  plotboxes.clear();

  for (auto& conf : datacardmodel.hists)
    draw_config(conf, plots);

  for (auto& conf : datacardmodel.flats)
    draw_config(conf, uncertainties);

  for (auto& conf : datacardmodel.rateparams)
    draw_config(conf, rateparams);

}


void DatacardController::on_add_plot () {

  draw_config(datacardmodel.hists.append(), plots);

}


void DatacardController::on_add_unc () {

  draw_config(datacardmodel.flats.append(), uncertainties);

}


void DatacardController::on_add_rate () {

  draw_config(datacardmodel.rateparams.append(), rateparams);

}
