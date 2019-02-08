#ifndef CROMBIE2_ALLMODELS_H
#define CROMBIE2_ALLMODELS_H


#include <map>
#include <string>

#include <crombie2/ConfigModel.h>


namespace crombie2 {
  class AllModels : public ConfigModel {
  public:
    /// Initialize with all of the models used
    template <typename ... Models> AllModels (Models& ... args) {
      add(args ...);
    }

    std::string get_name () const override;

  protected:
    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  private:

    void add (ConfigModel& config);

    template <typename ... Models> void add (ConfigModel& config, Models& ... args) {
      add(config);
      add(args ...);
    }

    std::map<std::string, ConfigModel*> models {};
  };
}


#endif
