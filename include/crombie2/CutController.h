#ifndef CROMBIE2_CUTCONTROLLER_H
#define CROMBIE2_CUTCONTROLLER_H

#include <crombie2/CutModel.h>
#include <crombie2/MiniCutController.h>


namespace crombie2 {
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

    CutModel& cutmodel;

    unsigned numcuts {0};

    std::list<Gtk::HBox> cutboxes {};
    Gtk::HBox selectionbox {};

    Gtk::HBox buttonbox {};
    Gtk::Entry labelentry {};
    Gtk::Button addcutbutton {"Add Cut String"};
    Gtk::Button addselectionbutton {"Define Selection"};

    std::list<MiniCutController> minicontrollers {};

  };
}


#endif
