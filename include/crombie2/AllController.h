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
    template <typename ... Controllers>
      AllController (ConfigPage& page, AllModels& model,
                     Controllers& ... args) :
      Controller {page, model, false}, allmodel {model} { add(args ...); }

    void redraw () override;

  private:

    void add (Controller& controller);

    template <typename ... Controllers> void add (Controller& controller, Controllers& ... args) {
      add(controller);
      add(args ...);
    }

    AllModels& allmodel;
    std::list<Controller*> controllers {};

  };
}


#endif
