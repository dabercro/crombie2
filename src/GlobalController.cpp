#include <crombie2/GlobalController.h>


using namespace crombie2;


GlobalController::GlobalController (ConfigPage& page, GlobalModel& model) :
  Controller {page, model}
{

  model.load_tag(last_tag);
  model.configs.draw(*this, page);
  add_update();

}
