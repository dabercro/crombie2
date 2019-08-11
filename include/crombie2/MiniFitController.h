#ifndef CROMBIE2_MINIFITCONTROLLER_H
#define CROMBIE2_MINIFITCONTROLLER_H

#include <crombie2/ConfigTable.h>
#include <crombie2/FitConfig.h>
#include <crombie2/RemoveWrapper.h>


namespace crombie2 {
  class MiniFitController {
  public:

    explicit MiniFitController (RemoveWrapper<FitConfig>& fit);

  private:

    RemoveWrapper<FitConfig>& fit;

    ConfigTable functiontable;
    ConfigTable parametertable {};


    void on_update_fit ();

    Gtk::HBox box {};
    Gtk::VBox functionlist {};
    Gtk::VBox guesslist {};
    Gtk::Button updatebutton {"Update fit"};

  };
}

#endif
