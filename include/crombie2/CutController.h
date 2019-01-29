#ifndef CROMBIE2_CUTCONTROLLER_H
#define CROMBIE2_CUTCONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/MiniCutController.h>
#include <crombie2/SelectionDisplay.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the CutModel
  */
  class CutController : public Controller {
  public:
    CutController (ConfigPage& page, CutModel& model);

  protected:
    void redraw () override;

  private:
    void on_add_cut ();
    void on_add_selection ();

    void add_cut (CutString& cutstring);
    void add_selection ();
    void fill_selection (Selection& selection);

    CutModel& cutmodel;

    unsigned numcuts {0};

    std::list<Gtk::HBox> cutboxes {};
    std::list<SelectionDisplay> selectiondisplays {};
    Gtk::HBox selectionbox {};

    Gtk::HBox buttonbox {};
    Gtk::Entry labelentry {};
    Gtk::Button addcutbutton {"Add Cut String"};
    Gtk::Button addselectionbutton {"Add Selection"};

    std::list<MiniCutController> minicontrollers {};

  };
}


#endif
