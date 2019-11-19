#ifndef CROMBIE2_ENVELOPES_H
#define CROMBIE2_ENVELOPES_H


#include <crombie2/Cuts.h>
#include <crombie2/BoolConfigurable.h>


namespace crombie2 {
  /**
     @brief A container for a combination of cuts.

     These cuts are expanded by the CutModel.
  */
  class Envelopes : public Cuts {
  public:
    Envelopes (const std::string& name = "");
    virtual ~Envelopes () = default;

    /// The string that joins the list of Cut values.
    BoolConfigurable joiner {"Process level"};
  };
}


#endif
