#ifndef CROMBIE2_MAINCONTROLLER_H
#define CROMBIE2_MAINCONTROLLER_H

#include <crombie2/ConfigPage.h>
#include <crombie2/GlobalController.h>


namespace crombie2 {
  class MainController {
  public:
    MainController (ConfigPage& globalpage,
                    ConfigPage& filespage,
                    ConfigPage& plotspage,
                    ConfigPage& selectionspage,
                    ConfigPage& uncpage);

  private:
    GlobalModel globalmodel {};
    GlobalController globalcontrol;

  };
}


#endif
