#include <crombie2/DatacardModel.h>
#include <crombie2/Misc.h>


using namespace crombie2;


std::string DatacardModel::get_name () const {

  return "datacard";

}


void DatacardModel::read (const Types::strings& config) {

  hists.clear();
  flats.clear();
  rateparams.clear();

  enum class mode {
    PLOTS,
    UNC,
    RATEPARAMS 
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
    else if (line == "RATE") {
      currentmode = mode::RATEPARAMS;
      continue;
    }    

    switch (currentmode) {
    case mode::PLOTS:
      hists.append().fill(line);
      break;
    case mode::UNC:
      flats.append().fill(line);
      break;
    case mode::RATEPARAMS:
      rateparams.append().fill(line);
      break;
    default:
      throw;
    }

  }

}


std::list<std::string> DatacardModel::serialize () const {

  std::list<std::string> output {};

  output.emplace_back(outdir);

  for (auto& hist : hists)
    output.emplace_back(hist.dump());

  output.emplace_back("UNC");

  for (auto& unc : flats)
    output.emplace_back(unc.dump());

  output.emplace_back("RATE");

  for (auto& rate : rateparams)
    output.emplace_back(rate.dump());

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


const RateParams* DatacardModel::get_rateparams (const std::string& proc) const {

  for (auto& rate : rateparams) {
    if (rate.has_process(proc))
      return &rate;
  }

  return nullptr;

}
