#include <crombie2/EnvelopeModel.h>
#include <crombie2/Misc.h>


using namespace crombie2;


std::string EnvelopeModel::get_name () const {
  return "envelopes";
}


void EnvelopeModel::read (const Types::strings& config) {
  list.clear();

  Cuts* cuts = nullptr;

  for (auto& line : config) {

    if (line.back() == ':') {
      cuts = &add();
      cuts->name.set(Misc::tokenize(line).front());
    }

    else if (cuts and line.size())
      cuts->add_cut().set(line);

  }

}


std::list<std::string> EnvelopeModel::serialize () const {

  std::list<std::string> output {};

  for (const auto& cuts : list) {
    output.emplace_back(cuts.name.get() + " :");

    for (const auto& cut : cuts.get_cuts())
      output.emplace_back(cut.get());
  }

  return output;

}


bool EnvelopeModel::is_valid (Tree& tree) const {

  for (const auto& cuts : list) {
    for (const auto& cut : cuts.get_cuts()) {
      if (not tree.is_valid(cut.get()))
        return false;
    }
  }

  return true;

}


RemoveWrapper<EnvelopeModel::cutstype>& EnvelopeModel::add_cutstring (const std::string& label) {

  return list.append(cutstype(label));

}
