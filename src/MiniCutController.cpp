#include <crombie2/MiniCutController.h>


using namespace crombie2;


template<> MiniCutController<CutString>::MiniCutController (RemoveWrapper<CutString>& cutstring) :
  cutstring {cutstring},
  labeltable{&(cutstring.name), &(cutstring.joiner)}
{
  init();
};
