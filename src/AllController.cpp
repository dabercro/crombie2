#include <crombie2/AllController.h>


using namespace crombie2;


void AllController::redraw () {

  for (auto& controller : controllers)
    controller->redraw();

}


void AllController::add (Controller& controller) {

  controllers.emplace_back(&controller);

}
