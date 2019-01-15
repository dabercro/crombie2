#ifndef CROMIBE2_GLOBALCONTROLLER_H
#define CROMIBE2_GLOBALCONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/GlobalModel.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the GlobalModel
  */
  class GlobalController : public Controller {

  public:
    GlobalController (ConfigPage& page, GlobalModel& model);

  protected:
    void redraw () override;

  private:
    GlobalModel& globalmodel;

  };
}


#endif
