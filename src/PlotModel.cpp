#include <regex>

#include <crombie2/PlotModel.h>


using namespace crombie2;


std::string PlotModel::get_name () {
  return "plots";
}


PlotModel::Plot& PlotModel::add_plot () {
  plots.emplace_back();
  return plots.back();
}



void PlotModel::read (const Types::strings& config) {
  std::regex expr {"'([^']+)',\\s*(\\d+),\\s*(-?[\\d\\.]+),\\s*(-?[\\d\\.]+),\\s*'([^']+)'(,\\s*'([^']+)',\\s*'([^']+)')?"};
  std::smatch matches;

  for (auto& line : config) {
    if (std::regex_match(line, matches, expr)) {
      auto& plot = add_plot();
      for (unsigned imatch = 0; imatch < 5; imatch++)
        plot.table.get_confs()[imatch]->set(matches[imatch + 1]);

      plot.data_var.set(matches[7]);
      plot.mc_var.set(matches[8]);

    }
  }

}


std::list<std::string> PlotModel::serialize () {
  std::list<std::string> output {};
  for (auto& plot : plots) {
    std::string line =
      std::string("'") +
      plot.name.get() + "', " +
      plot.nbins.get() + ", " +
      plot.min.get() + ", " +
      plot.max.get() + ", " +
      plot.label.get();
    if (plot.data_var.get().size() and plot.mc_var.get().size())
      line += std::string(", '") +
        plot.data_var.get() + "', '" +
        plot.mc_var.get() + "'";
    output.push_back(line);
  }
  return output;
}
