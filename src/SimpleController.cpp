#include <crombie2/SimpleController.h>


using namespace crombie2;


SimpleController::SimpleController (ConfigPage& page, SimpleModel& model) :
  Controller {page, model},
  simplemodel {model}
{

  simplemodel.draw(page.box());

}


void SimpleController::redraw () {

  simplemodel.redraw();

}
