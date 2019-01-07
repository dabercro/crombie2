#ifndef CROMBIE2_MINICUTCONTROLLER_H
#define CROMBIE2_MINICUTCONTROLLER_H


#include <crombie2/ConfigTable.h>
#include <crombie2/CutString.h>


namespace crombie2 {
  class MiniCutController {
  public:
    MiniCutController(Controller& controller, CutString& cutstring);

    void draw (Gtk::Box& page);

  private:
    Controller& controller;
    CutString& cutstring;
    ConfigTable labeltable;
    ConfigTable cuttable;

    void on_add_cut ();

    Gtk::HBox box {};
    Gtk::VBox labellist {};
    Gtk::VBox cutlist {};
    Gtk::Button addbutton {"Add Cut"};

  };
}


#endif
