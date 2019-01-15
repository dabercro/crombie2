#ifndef CROMBIE2_CUTMODEL_H
#define CROMBIE2_CUTMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/CutString.h>
#include <crombie2/Selection.h>


namespace crombie2 {
  /**
     @brief The ConfigModel for the selections for analysis
  */
  class CutModel : public ConfigModel {

  public:

    std::string get_name () const override;

    CutString& add_cutstring (const std::string& label, const std::string& joiner = "&&");

    /// Expands a cutstring for viewing
    std::string expand (const std::string& cutlabel) const;

    /// Returns the list of labels
    const std::list<std::string>& get_labels () const;

    /// Returns a cut based on it's label
    CutString& get_cutstring (const std::string& label);

    std::list<Selection> selections {};

    bool is_valid () const override;

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

    /// Holds the cut strings
    std::map<std::string, CutString> cutstrings;

    /// Keeps the cut labels in order
    std::list<std::string> cutlabels;

  };
}


#endif
