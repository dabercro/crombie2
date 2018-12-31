#ifndef CROMBIE2_MAINCONTROLLER_H
#define CROMBIE2_MAINCONTROLLER_H

#include <crombie2/CutController.h>
#include <crombie2/GlobalController.h>
#include <crombie2/PlotController.h>


namespace crombie2 {
  class MainController {
  public:
    MainController (ConfigPage& globalpage,
                    ConfigPage& filepage,
                    ConfigPage& plotpage,
                    ConfigPage& selectionpage,
                    ConfigPage& uncertaintypage);

  private:
    CutModel cutmodel {};
    CutController cutcontrol;

    GlobalModel globalmodel {};
    GlobalController globalcontrol;

    PlotModel plotmodel {};
    PlotController plotcontrol;

  };
}


#endif
