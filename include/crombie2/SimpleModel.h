#ifndef CROMBIE2_SIMPLEMODEL_H
#define CROMBIE2_SIMPLEMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/ConfigTable.h>


namespace crombie2 {
  /**
     @brief A config model that just consists of a list of configurables.

     This is an abstract class which does not implement get_name()
  */
  class SimpleModel : public ConfigModel {
  public:
    /// Constructor which passes arguments to the internal ConfigTable
    SimpleModel (std::initializer_list<GuiConfigurable*> initialize,
                 const bool horizontal = false);

    /// A ConfigTable which is initialized by the child classes
    ConfigTable configs;

  protected:
    /// Copy another SimpleModel to this one
    void copy (const SimpleModel& other);

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  };
}


#endif
