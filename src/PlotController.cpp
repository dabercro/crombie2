#include <crombie2/PlotController.h>


using namespace crombie2;


PlotController::PlotController (ConfigPage& page, PlotModel& model) :
  Controller {page, model},
  plotmodel {model}
{

  buttonbox.pack_start(addbutton, Gtk::PACK_EXPAND_PADDING);
  page.pack_start(buttonbox, Gtk::PACK_SHRINK);

  addbutton.set_border_width(10);

  buttonbox.show();
  addbutton.show();
  addbutton.signal_clicked().
    connect(sigc::mem_fun(*this, &PlotController::on_add_plot));

  redraw();

}

void PlotController::redraw () {

  plotted = 0;
  boxes.clear();

  for (auto& plot : plotmodel.plots)
    add_table(plot);

}


void PlotController::add_table (RemoveWrapper<Plot>& plot) {

  if (((plotted++) % 4) == 0) {
    boxes.emplace_back();
    page.box().pack_start(boxes.back(), Gtk::PACK_SHRINK);
    boxes.back().show();
  }

  auto& box = boxes.back();

  plot.table.draw(box);

  box.pack_start(plot.remove, Gtk::PACK_SHRINK);
  plot.remove.show();

}


void PlotController::on_add_plot() {

  auto& plot = plotmodel.add_plot();
  add_table(plot);

}
