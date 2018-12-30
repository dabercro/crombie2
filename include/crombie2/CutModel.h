#ifndef CROMBIE2_CUTMODEL_H
#define CROMBIE2_CUTMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/CutString.h>


namespace crombie2 {
  class CutModel : public ConfigModel {

  public:

    std::string get_name () const override;

    /// Expands a cutstring for viewing
    std::string expand (const std::string& cutlabel) const;

    /// Returns the list of labels
    const std::list<std::string>& get_labels () const;

    /// Returns a cut based on it's label
    const CutString& get_cutstring (const std::string& label) const;

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
