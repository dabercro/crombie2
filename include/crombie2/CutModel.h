#ifndef CROMBIE2_CUTMODEL_H
#define CROMBIE2_CUTMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/CutString.h>
#include <crombie2/Selection.h>
#include <crombie2/Tree.h>


namespace crombie2 {
  /**
     @brief The ConfigModel for the selections for analysis
  */
  class CutModel : public ConfigModel {

  public:

    using cutstype = CutString;

    std::string get_name () const override;

    RemoveWrapper<cutstype>& add_cutstring (const std::string& label, const std::string& joiner = "&&");

    /// Expands a cutstring for viewing
    std::string expand (const std::string& cutlabel) const;

    /// Returns the list of labels
    std::list<std::string> get_labels () const;

    /// Returns a cut based on it's label
    RemoveWrapper<CutString>& get_cutstring (const std::string& label);

    RemoveList<Selection> selections {};

    bool is_valid () const override;
    bool is_valid (Tree& tree, bool skip_branch_check = false) const;

    /**
       @param label Is the cut to get the cutflow cuts for
       @returns The list of cuts to make a cutflow table for the given label
    */
    std::vector<std::string> cutflow (const std::string& label) const;

    /// Gets the labels for a plot
    std::vector<std::string> labels (const std::string& label) const;

  private:

     RemoveWrapper<CutString>& at (const std::string& label);
     const RemoveWrapper<CutString>& at (const std::string& label) const;

     void read (const Types::strings& config) override;

     std::list<std::string> serialize () const override;

     /// Holds the cut strings
     RemoveList<CutString> cutstrings {};

  };
}


#endif
