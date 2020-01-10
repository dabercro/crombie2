#include <crombie2/CutString.h>
#include <crombie2/Envelopes.h>
#include <crombie2/MiniCutController.h>


using namespace crombie2;


template<> MiniCutController<CutString>::MiniCutController (RemoveWrapper<CutString>& cutstring) :
  cutstring {cutstring},
  labeltable{&(cutstring.name), &(cutstring.joiner), &(cutstring.label)}
{
  init();
};

template<> MiniCutController<Envelopes>::MiniCutController (RemoveWrapper<Envelopes>& cutstring) :
  cutstring {cutstring},
  labeltable{&(cutstring.name), &(cutstring.joiner)}
{
  init();
};

template<> MiniCutController<Cuts>::MiniCutController (RemoveWrapper<Cuts>& cutstring) :
  cutstring {cutstring},
  labeltable{&(cutstring.name)}
{
  init();
};
