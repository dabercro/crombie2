#ifndef CROMBIE2_HISTMODEL_H
#define CROMBIE2_HISTMODEL_H


#include <crombie2/HistAnalyzer.h>
#include <crombie2/ConfigModel.h>
#include <crombie2/HistSplit.h>


namespace crombie2 {
  class HistModel : public ConfigModel {
  public:
    HistModel (Job& job, const GlobalModel& globalmodel,
               const Plot& plot, const CutModel& cutmodel, const Selection& selection);

    std::string get_name () const override;

    HistSplit get_histsplit () const;

  protected:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

    std::vector<HistAnalyzer> analyzers {};    ///< Analyzers are only needed when the hist isn't already cached

  };
}


#endif
