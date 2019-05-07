#include <crombie2/MiniFitController.h>


using namespace crombie2;


MiniFitController::MiniFitController (RemoveWrapper<FitConfig>& fit) :
  fit {fit},
  functiontable {&fit}
{

}
