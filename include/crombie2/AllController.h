#ifndef CROMIBE2_ALLCONTROLLER_H
#define CROMIBE2_ALLCONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/AllModels.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the AllModels
  */
  class AllController : public Controller {

  public:
    AllController (ConfigPage& page, AllModels& model,
                   std::map<std::string, ConfigPage>& pagemap);

    void redraw () override;

  private:

    std::list<Controller*> controllers {};

  };
}


#endif
