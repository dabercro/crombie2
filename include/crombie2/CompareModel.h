#ifndef CROMBIE2_COMPAREMODEL_H
#define CROMBIE2_COMPAREMODEL_H


#include <crombie2/Compare.h>
#include <crombie2/CutModel.h>
#include <crombie2/ListModel.h>
#include <crombie2/PlotModel.h>


namespace crombie2 {

  class CompareModel : public ListModel<Compare> {

  public:
    std::string get_name () const override;

    const Compare* get (const std::string name) const;

    bool is_valid (const CutModel& cuts, const PlotModel& plots, bool batch = false) const;

  private:
    void read (const Types::strings& config) override;
    std::list<std::string> serialize () const override;

  };
}


#endif
