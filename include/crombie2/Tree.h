#ifndef CROMBIE2_TREE_H
#define CROMBIE2_TREE_H


#include <memory>

#include <crombie2/Types.h>

#include "TBranch.h"
#include "TFile.h"
#include "TTree.h"
#include "TTreeFormula.h"


namespace crombie2 {
  /**
     @brief Reads a TTree from a .root file and tracks desired formula results
  */
  class Tree {
  public:

    Tree (const std::string& infile, const std::string& treename);
    ~Tree ();


    /**
       Fill the tree with the next event's branch contents.
       @returns False when there are no more events to read.
    */
    inline bool next() {
      if (ientry == nentries)
        return false;
      // Get the branch entries directly to avoid TBranchElement locking
      for (auto* branch : branches_to_read)
        branch->GetEntry(ientry);
      ientry++;
      for (auto& form : forms)
        form.second.first = form.second.second->EvalInstance();
      return true;
    }


    /**
       Get a reference to where the result for a TTreeFormula
       @param expr The expression to turn into a TTreeFormula for this tree
    */
    double& request (const std::string& expr);


    /**
       Get a bare pointer to a TObject inside of this file.
       @param name is the name of the object, searched for with TFile::Get
    */
    template<typename C> C* get(const std::string& name) {
      auto* obj = dynamic_cast<C*>(file->Get(name.data()));
      if (not obj)
        throw std::runtime_error(std::string("Could not find object '") + name + "' in " + file->GetName());
      return obj;
    }

  private:

    TFile* file;          ///< The TFile that is being read
    TTree* tree;          ///< Holds the pointer to the tree
    long long nentries;   ///< Total number of events in the tree
    long long ientry {0}; ///< Which entry are we on

    /// Hold all of the TTreeFormulas for this tree
    Types::map<std::pair<double, std::unique_ptr<TTreeFormula>>> forms {};

    /// Hold the branches to be read to skip locking
    std::vector<TBranch*> branches_to_read {};

  };
}


#endif
