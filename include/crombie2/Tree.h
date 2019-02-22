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
     @brief Reads a TTree from a .root file and tracks desired formula results.

     Before the tree is looped over, requests can be made to activate branches to read.
     Pointers to other TObjects can also be gathered through the Tree::get<> function.
  */
  class Tree {
  public:

    Tree (const std::string& infile, const std::string& treename);
    ~Tree ();


    /**
       @brief Fill the branches with the next event's contents.
       @returns False when there are no more events to read.
    */
    bool next();


    /**
       @brief Get a reference to where the result for a TTreeFormula will be.
       @param expr The expression to turn into a TTreeFormula for this tree
    */
    double& request (const std::string& expr);


    /**
       @brief Get a bare pointer to a TObject inside of this file.
       @param name is the name of the object, searched for with TFile::Get
    */
    template<typename C> C* get(const std::string& name) {
      auto* obj = dynamic_cast<C*>(file->Get(name.data()));
      if (not obj)
        throw std::runtime_error(std::string("Could not find object '") + name + "' in " + file->GetName());
      return obj;
    }


    /// Get the maximum value of an expression
    double max (const std::string& branch);

    std::shared_ptr<TTreeFormula> get_formula (const std::string& expr);

  private:

    TFile* file;          ///< The TFile that is being read
    TTree* tree;          ///< Holds the pointer to the tree
    long long nentries;   ///< Total number of events in the tree
    long long ientry {0}; ///< Which entry are we on

    /// Hold all of the TTreeFormulas for this tree
    Types::map<std::pair<double, std::shared_ptr<TTreeFormula>>> forms {};

  };
}


#endif
