#ifndef CROMBIE2_MAINCONTROLLER_H
#define CROMBIE2_MAINCONTROLLER_H

#include <crombie2/CutController.h>
#include <crombie2/FileController.h>
#include <crombie2/GlobalController.h>
#include <crombie2/PlotController.h>


namespace crombie2 {
  class MainController {
  public:
    MainController (ConfigPage& globalpage,
                    ConfigPage& filepage,
                    ConfigPage& plotpage,
                    ConfigPage& selectionpage,
                    ConfigPage& uncertaintypage,
                    ConfigPage& jobpage);

  private:
    CutModel cutmodel {};
    CutController cutcontrol;

    FileModel filemodel {};
    FileController filecontrol;

    GlobalModel globalmodel {};
    GlobalController globalcontrol;

    PlotModel plotmodel {};
    PlotController plotcontrol;

    ConfigPage& jobpage;

    void on_submit_job ();

    Gtk::Button button {"Submit"};

  };
}


#endif
