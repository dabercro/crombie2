#include <regex>

#include <crombie2/PlotModel.h>


using namespace crombie2;


std::string PlotModel::get_name () const {
  return "plots";
}


void PlotModel::read (const Types::strings& config) {
  list.clear();

  std::regex expr {"'([^']+)',\\s*(\\d+),\\s*(-?[\\d\\.]+),\\s*(-?[\\d\\.]+),\\s*'([^']+)'(,\\s*'([^']+)',\\s*'([^']+)')?"};
  std::smatch matches;

  for (auto& line : config) {
    if (std::regex_match(line, matches, expr)) {
      auto& plot = add();
      for (unsigned imatch = 0; imatch < 5; imatch++)
        plot.get_confs()[imatch]->set(matches[imatch + 1]);

      plot.data_var.set(matches[7]);
      plot.mc_var.set(matches[8]);

    }
  }

}


std::list<std::string> PlotModel::serialize () const {

  std::list<std::string> output {};

  for (auto& plot : list) {
    if (not plot.name.get().size())
      continue;

    std::string line =
      std::string("'") +
      plot.name.get() + "', " +
      plot.nbins.get() + ", " +
      plot.min.get() + ", " +
      plot.max.get() + ", '" +
      plot.label.get() + "'";
    if (plot.data_var.get().size() and plot.mc_var.get().size())
      line += std::string(", '") +
        plot.data_var.get() + "', '" +
        plot.mc_var.get() + "'";
    output.push_back(line);
  }

  return output;

}
