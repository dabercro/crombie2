#ifndef CROMBIE2_MINICUTCONTROLLER_H
#define CROMBIE2_MINICUTCONTROLLER_H


#include <crombie2/ConfigTable.h>
#include <crombie2/CutString.h>
#include <crombie2/RemoveWrapper.h>


namespace crombie2 {
  /**
     @brief Handles the GUI interaction for each CutString that is part of the CutModel
  */
  class MiniCutController {
  public:
    explicit MiniCutController(RemoveWrapper<CutString>& cutstring);

    void draw (Gtk::Box& page);

  private:
    RemoveWrapper<CutString>& cutstring;
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
