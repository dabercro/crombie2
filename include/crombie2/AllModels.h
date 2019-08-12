#ifndef CROMBIE2_ALLMODELS_H
#define CROMBIE2_ALLMODELS_H


#include <exception>

#include <crombie2/ConfigModel.h>
#include <crombie2/ConfigPage.h>


namespace crombie2 {
  class AllModels : public ConfigModel {
  public:
    /// Initialize with all of the models used
    AllModels (std::map<std::string, ConfigPage>& pagemap);

    std::string get_name () const override;

    template <class M>
    const M& get () const {
      auto* ptr = dynamic_cast<M*>(models.at(M().get_name()));
      return *ptr;
    }

  protected:
    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  private:

    Types::map<ConfigModel*> models {};
  };
}


#endif
