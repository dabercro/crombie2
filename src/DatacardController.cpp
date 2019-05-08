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
    draw_plot(hist);

  page.draw(plots);
  page.draw(plotbutton);

  plotbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &DatacardController::on_add_plot));

}


void DatacardController::redraw () {

  plotboxes.clear();

  for (auto& hist : datacardmodel.hists)
    draw_plot(hist);

}


void DatacardController::on_add_plot () {

  draw_plot(datacardmodel.hists.append());

}


void DatacardController::draw_plot (RemoveWrapper<SelectionPlot>& plot) {

  auto& box = plotboxes.emplace_back();

  plot.draw(box);
  box.pack_start(plot.remove, Gtk::PACK_SHRINK);
  plot.remove.show();

  plot.also_remove([&box, this] () {
      plotboxes.remove_if([&box] (auto& ele) {
          return &box == &ele;
        });
    });

  plots.pack_start(box, Gtk::PACK_SHRINK);

  box.show();

}
