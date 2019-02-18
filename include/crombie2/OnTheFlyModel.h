#ifndef CROMBIE2_ONTHEFLYMODEL_H
#define CROMBIE2_ONTHEFLYMODEL_H


#include <crombie2/ListModel.h>
#include <crombie2/ReweightReader.h>


namespace crombie2 {
  /**
     @brief The ConfigModel that handles a list of reweights to make on the fly
  */
  class OnTheFlyModel : public ListModel<ReweightReader> {

  public:
    std::string get_name () const override;

  private:
    void read (const Types::strings& config) override;
    std::list<std::string> serialize () const override;

  };
}



#endif
