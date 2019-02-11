#ifndef CROMIBE2_SIMPLECONTROLLER_H
#define CROMIBE2_SIMPLECONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/SimpleModel.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the SimpleModel
  */
  class SimpleController : public Controller {

  public:
    SimpleController (ConfigPage& page, SimpleModel& model);

    void redraw () override;

  private:
    SimpleModel& simplemodel;

  };
}


#endif
