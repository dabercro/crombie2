#include <crombie2/GlobalModel.h>


using namespace crombie2;


std::string GlobalModel::get_name () const {
  return "globals";
}


void GlobalModel::read (const Types::strings& config) {
  auto iter = config.begin();
  for (auto* configurable : configs.get_confs())
    configurable->set(*iter++);
}


std::list<std::string> GlobalModel::serialize () const {
  std::list<std::string> output {};
  for (auto* configurable : configs.get_confs())
    output.push_back(configurable->get());

  return output;
}
