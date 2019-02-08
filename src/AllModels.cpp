#include <crombie2/AllModels.h>
#include <crombie2/Misc.h>


using namespace crombie2;


std::string AllModels::get_name () const {

  return "all";

}


void AllModels::read (const Types::strings& config) {

  for (auto& line : config) {

    // First is the name, next is the file for the other model
    auto split = Misc::tokenize(line);

    models.at(split.front())->load(split.back());

  }

}


std::list<std::string> AllModels::serialize () const {

  std::list<std::string> output {};

  for (auto& model : models)
    output.push_back(model.first + "   " + model.second->save());

  return output;

}


void AllModels::add (ConfigModel& config) {

  models.insert({config.get_name(), &config});

}
