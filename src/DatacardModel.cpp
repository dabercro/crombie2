#include <crombie2/DatacardModel.h>
#include <crombie2/Misc.h>


using namespace crombie2;


std::string DatacardModel::get_name () const {

  return "datacard";

}


void DatacardModel::read (const Types::strings& config) {

  hists.clear();

  enum class mode {
    PLOTS,
    UNCERTAINTIES
  };

  mode currentmode {mode::PLOTS};

  auto iterator = config.begin();
  outdir.set(*(iterator++));
  while (iterator != config.end()) {
    auto& line = *(iterator++);
    if (line == "UNC") {
      currentmode = mode::UNCERTAINTIES;
      continue;
    }    
    auto tokens = Misc::tokenize(line);
    if (currentmode == mode::PLOTS) {
      auto& newhist = hists.append();
      newhist.selection.set(tokens[0]);
      newhist.plot.set(tokens[1]);
    }
  }

}


std::list<std::string> DatacardModel::serialize () const {

  std::list<std::string> output {};

  output.emplace_back(outdir);

  for (auto& hist : hists)
    output.emplace_back(hist.selection.get() + " " + hist.plot.get());

  output.emplace_back("UNC");

  return output;

}
