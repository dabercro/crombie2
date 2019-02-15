#ifndef CROMBIE2_PLOTCONTROLLER_H
#define CROMBIE2_PLOTCONTROLLER_H

#include <gtkmm/buttonbox.h>

#include <crombie2/Controller.h>
#include <crombie2/PlotModel.h>

namespace crombie2 {
  /**
     @brief Handles the interactions between the GUI and the PlotModel object
  */
  class PlotController : public Controller {

  public:
    PlotController (ConfigPage& page, PlotModel& model);

    void redraw () override;

  private:
    void add_table (RemoveWrapper<Plot>& table);
    void on_add_plot ();

    PlotModel& plotmodel;

    unsigned plotted {0};

    std::list<Gtk::HBox> boxes {};
    Gtk::HButtonBox buttonbox {};
    Gtk::Button addbutton {"Add Plot"};

  };
}


#endif
