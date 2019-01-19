#include <crombie2/SimpleModel.h>


using namespace crombie2;


SimpleModel::SimpleModel (std::initializer_list<GuiConfigurable*> initialize,
                          const bool horizontal) :
  configs {initialize, horizontal} {}


void SimpleModel::copy (const SimpleModel& other) {

  auto iter = other.configs.get_confs().begin();
  for (auto* configurable : configs.get_confs())
    configurable->set((*iter++)->get());

}


void SimpleModel::read (const Types::strings& config) {

  auto iter = config.begin();
  for (auto* configurable : configs.get_confs()) {
    if (iter == config.end())
      break;
    configurable->set(*iter++);
  }

}


std::list<std::string> SimpleModel::serialize () const {

  std::list<std::string> output {};
  for (auto* configurable : configs.get_confs())
    output.push_back(configurable->get());

  return output;

}
