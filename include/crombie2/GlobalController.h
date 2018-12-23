#ifndef CROMIBE2_GLOBALCONTROLLER_H
#define CROMIBE2_GLOBALCONTROLLER_H

#include <crombie2/Controller.h>
#include <crombie2/ConfigPage.h>
#include <crombie2/GlobalModel.h>

namespace crombie2 {
  class GlobalController : public Controller {

  public:
    GlobalController (ConfigPage& page, GlobalModel& model);

  };
}


#endif
