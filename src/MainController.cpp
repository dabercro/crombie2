#include <crombie2/MainController.h>


using namespace crombie2;


MainController::MainController (ConfigPage& globalpage,
                                ConfigPage& filespage,
                                ConfigPage& plotspage,
                                ConfigPage& selectionspage,
                                ConfigPage& uncpage) :
  globalcontrol {globalpage, globalmodel} {}
