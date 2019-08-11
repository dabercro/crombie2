#ifndef CROMBIE2_FITCONTROLLER_H
#define CROMBIE2_FITCONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/FitModel.h>
#include <crombie2/MiniFitController.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the FitModel
  */
  class FitController : public Controller {
  public:
    FitController (ConfigPage& page, FitModel& model);

    void redraw () override;

  private:
    void on_add_fit ();

    void add_fit (RemoveWrapper<FitConfig>& fitstring);

    FitModel& fitmodel;

    unsigned numfits {0};

    std::list<Gtk::HBox> fitboxes {};

    Gtk::HBox buttonbox {};
    Gtk::Entry fitentry {};
    Gtk::Button addfitbutton {"Add Fit"};

    std::list<MiniFitController> minicontrollers {};

  };
}


#endif
