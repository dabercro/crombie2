#include <crombie2/SimpleModel.h>


using namespace crombie2;


SimpleModel::SimpleModel (std::initializer_list<GuiConfigurable*> initialize,
                          const bool horizontal) :
  ConfigTable {initialize, horizontal} {}


void SimpleModel::read (const Types::strings& config) {

  auto iter = config.begin();
  for (auto* configurable : get_confs()) {
    if (iter == config.end())
      break;
    auto line = *iter++;
    configurable->set(line == "_" ? "" : line);
  }

}


std::list<std::string> SimpleModel::serialize () const {

  std::list<std::string> output {};
  for (auto* configurable : get_confs()) {
    auto line = configurable->get();
    output.push_back(line.size()
                     ? configurable->get()
                     : "_");
  }

  return output;

}
