#include <crombie2/MainController.h>


using namespace crombie2;


MainController::MainController (ConfigPage& globalpage,
                                ConfigPage& filepage,
                                ConfigPage& plotpage,
                                ConfigPage& selectionpage,
                                ConfigPage& uncertaintypage) :
  globalcontrol {globalpage, globalmodel},
  plotcontrol {plotpage, plotmodel} {}