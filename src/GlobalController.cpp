#include <crombie2/GlobalController.h>


using namespace crombie2;


GlobalController::GlobalController (ConfigPage& page, GlobalModel& model) :
  Controller {page, model},
  globalmodel {model}
{

  globalmodel.configs.draw(*this, page.box());

}


void GlobalController::redraw () {

  globalmodel.configs.redraw(*this);

}
