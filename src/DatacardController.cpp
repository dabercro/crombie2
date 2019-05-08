#include <crombie2/DatacardController.h>


using namespace crombie2;


DatacardController::DatacardController (ConfigPage& page, DatacardModel& model) :
  Controller {page, model},
  datacardmodel {model},
  info {&model.outdir}
{



}


void DatacardController::redraw () {



}
