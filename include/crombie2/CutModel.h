#ifndef CROMBIE2_CUTMODEL_H
#define CROMBIE2_CUTMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/CutString.h>
#include <crombie2/Selection.h>
#include <crombie2/RemoveWrapper.h>


namespace crombie2 {
  /**
     @brief The ConfigModel for the selections for analysis
  */
  class CutModel : public ConfigModel {

  public:

    CutModel () = default;
    CutModel (const CutModel& other);

    std::string get_name () const override;

    RemoveWrapper<CutString>& add_cutstring (const std::string& label, const std::string& joiner = "&&");

    /// Expands a cutstring for viewing
    std::string expand (const std::string& cutlabel) const;

    /// Returns the list of labels
    std::list<std::string> get_labels () const;

    /// Returns a cut based on it's label
    RemoveWrapper<CutString>& get_cutstring (const std::string& label);

    std::list<RemoveWrapper<Selection>> selections {};

    bool is_valid () const override;

    /**
       @param label Is the cut to get the cutflow cuts for
       @returns The list of cuts to make a cutflow table for the given label
    */
    std::vector<std::string> cutflow (const std::string& label) const;

  private:

     RemoveWrapper<CutString>& at (const std::string& label);
     const RemoveWrapper<CutString>& at (const std::string& label) const;

     void read (const Types::strings& config) override;

     std::list<std::string> serialize () const override;

     /// Holds the cut strings
     std::list<RemoveWrapper<CutString>> cutstrings {};

  };
}


#endif
