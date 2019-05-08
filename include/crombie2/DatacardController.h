#ifndef CROMIBE2_DATACARDCONTROLLER_H
#define CROMIBE2_DATACARDCONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/DatacardModel.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the DatacardModel
  */
  class DatacardController : public Controller {

  public:
    DatacardController (ConfigPage& page, DatacardModel& model);

    void redraw () override;

  private:
    DatacardModel& datacardmodel;

    ConfigTable info;

    Gtk::Label plotlabel {"Plots"};
    Gtk::VBox plots {};
    Gtk::Label unclabel {"Uncertainties"};
    Gtk::VBox uncertainties {};

  };
}


#endif
