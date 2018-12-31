#ifndef CROMBIE2_CUTMODEL_H
#define CROMBIE2_CUTMODEL_H


#include <crombie2/ConfigTable.h>
#include <crombie2/CutString.h>


namespace crombie2 {
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

    class Selection {
    public:
      Selection (const std::string& cut, const std::string& data, const std::string& mc);
      Configurable<std::string> cut;
      Configurable<std::string> data_weight;
      Configurable<std::string> mc_weight;
      ConfigTable table {
        &cut, &data_weight, &mc_weight
      };
    };

    std::list<Selection> selections {};

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
