#ifndef CROMBIE2_COMPAREMODEL_H
#define CROMBIE2_COMPAREMODEL_H


#include <crombie2/ListModel.h>
#include <crombie2/Compare.h>


namespace crombie2 {

  class CompareModel : public ListModel<Compare> {

  public:
    std::string get_name () const override;

  private:
    void read (const Types::strings& config) override;
    std::list<std::string> serialize () const override;

  };
}


#endif
