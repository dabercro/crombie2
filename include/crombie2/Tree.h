#ifndef CROMBIE2_TREE_H
#define CROMBIE2_TREE_H


#include <crombie2/Types.h>


#include "TFile.h"
#include "TTree.h"
#include "TTreeFormula.h"


namespace crombie2 {
  class Tree {
  public:
    Tree (const std::string& infile, const std::string& treename);
    ~Tree ();

    bool next();

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

    Types::map<std::pair<double, TTreeFormula*>> forms {};

    /// Holds all of the branches that need to be read
    std::set<std::string> needed;

  };
}


#endif
