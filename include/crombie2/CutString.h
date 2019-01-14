#ifndef CROMBIE2_CUTSTRING_H
#define CROMBIE2_CUTSTRING_H


#include <list>

#include <crombie2/Configurable.h>
#include <crombie2/Cut.h>
#include <crombie2/JoinerConfigurable.h>


namespace crombie2 {
  /**
     A container for a combination of cuts.
     These cuts are expanded by the CutModel.
  */
  class CutString {
  public:
    CutString (const std::string& name, const std::string& joiner);

    /// Add a cut to this CutString and return a reference to what's added
    Cut& add_cut ();

    /// Get the list of cuts to loop over
    std::list<Cut>& get_cuts ();
    const std::list<Cut>& get_cuts () const;

    /// The name of the cut, which is configurable
    Configurable<std::string> name;

    /// The string that joins the list of Cut values.
    JoinerConfigurable joiner;

  private:
    /// A list of cuts, to prevent reallocation
    std::list<Cut> cuts;

  };
}


#endif
