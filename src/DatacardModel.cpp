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
    UNC
  };

  mode currentmode {mode::PLOTS};

  auto iterator = config.begin();
  outdir.set(*(iterator++));
  while (iterator != config.end()) {
    auto& line = *(iterator++);
    if (line == "UNC") {
      currentmode = mode::UNC;
      continue;
    }    

    auto tokens = Misc::tokenize(line);
    if (currentmode == mode::PLOTS) {
      auto& newhist = hists.append();
      newhist.selection.set(tokens[0]);
      newhist.plot.set(tokens[1]);
    }
    else if (currentmode == mode::UNC) {
      auto& newflat = flats.append();
      newflat.name.set(tokens[0]);
      newflat.shape.set(tokens[1]);
      newflat.value.set(tokens[2]);
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


bool DatacardModel::is_valid (const CutModel& cuts, const PlotModel& plots, bool batch) const {

  for (auto& hist : hists) {
    try {
      bool found = false;
      auto plotname = hist.plot.get();
      for (auto& plot : plots.list) {
        if (plotname == plot.name.get()) {
          found = true;
          break;
        }
      }
      if (not found) {
        if (not batch)
          Misc::message("Can't find plot", std::string("Plot \"") + plotname + "\" does not seem to be configured");
        return false;
      }
    }
    catch (const std::exception& e) {
      return false;
    }
  }

  return true;

}
