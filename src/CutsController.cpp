#include <crombie2/CutModel.h>
#include <crombie2/CutsController.h>
#include <crombie2/EnvelopeModel.h>


using namespace crombie2;


template<> void CutsController<EnvelopeModel>::redraw () {

  numcuts = 0;
  cutboxes.clear();
  minicontrollers.clear();

  for (auto& cut : cutmodel.list)
    add_cut(cut);

}

template<> void CutsController<CutModel>::redraw () {
  // This gets overridden anyway
}
