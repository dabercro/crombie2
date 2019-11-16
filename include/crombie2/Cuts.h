#ifndef CROMBIE2_CUTS_H
#define CROMBIE2_CUTS_H


#include <crombie2/Configurable.h>
#include <crombie2/Cut.h>
#include <crombie2/RemoveList.h>


namespace crombie2 {

  class Cuts {

  public:
    Cuts (const std::string& name = "");
    virtual ~Cuts () = default;

    /// Add a cut to this CutString and return a reference to what's added
    Cut& add_cut ();

    /// Get the list of cuts to loop over
    RemoveList<Cut>& get_cuts ();
    const RemoveList<Cut>& get_cuts () const;

    /// The name of the cut, which is configurable
    Configurable<std::string> name;


  protected:

    /// A list of cuts, to prevent reallocation
    RemoveList<Cut> cuts;

  };

}


#endif
