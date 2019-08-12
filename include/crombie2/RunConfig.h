#ifndef CROMBIE2_RUNCONFIG_H
#define CROMBIE2_RUNCONFIG_H


#include <map>
#include <string>


namespace crombie2 {
  class RunConfig {

  public:

    std::map<std::string, std::string> dirs;
    bool docutflow;
    bool dolumi;
    bool doreweight;
    bool dofit;

  };
}


#endif
