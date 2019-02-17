#include <crombie2/AllController.h>


using namespace crombie2;


AllController::AllController (ConfigPage& page, AllModels& model,
                              std::map<std::string, ConfigPage>& pagemap) :
  Controller {page, model, false}
{

  for (auto& page : pagemap)
    controllers.emplace_back(&page.second.get_controller());

}

void AllController::redraw () {

  for (auto* controller : controllers)
    controller->redraw();

}
