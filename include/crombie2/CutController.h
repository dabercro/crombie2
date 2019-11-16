#ifndef CROMBIE2_CUTCONTROLLER_H
#define CROMBIE2_CUTCONTROLLER_H


#include <crombie2/CutsController.h>
#include <crombie2/SelectionDisplay.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the CutModel
  */
  class CutController : public CutsController<CutModel> {
  public:

    CutController (ConfigPage& page, CutModel& model);

    void redraw () override;

  private:
    void on_add_selection ();

    void add_selection ();
    void fill_selection (RemoveWrapper<Selection>& selection);

    std::list<SelectionDisplay> selectiondisplays {};
    Gtk::HBox selectionbox {};

    Gtk::Button addselectionbutton {"Add Selection"};

  };
}


#endif
