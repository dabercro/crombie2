#ifndef CROMBIE2_CUTSTRING_H
#define CROMBIE2_CUTSTRING_H


#include <crombie2/Cuts.h>
#include <crombie2/JoinerConfigurable.h>


namespace crombie2 {
  /**
     @brief A container for a combination of cuts.

     These cuts are expanded by the CutModel.
  */
  class CutString : public Cuts {
  public:
    CutString (const std::string& name, const std::string& joiner);
    virtual ~CutString () = default;

    /// The string that joins the list of Cut values.
    JoinerConfigurable joiner;
  };
}


#endif
