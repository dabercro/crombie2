#include "catch.hpp"
#include "utils.h"

#include <crombie2/PlotModel.h>


TEST_CASE("Test Plot Lines") {

  test_dir("testplot");

  crombie2::PlotModel model {};

  REQUIRE(model.list.size() == 0);

  auto& plot = model.add();

  REQUIRE(plot.lines.get() == "");

  REQUIRE(plot.vert_lines().size() == 0);

  plot.name.set("test");
  plot.lines.set("0.5 1.0 2.0");

  std::vector<double> expected {0.5, 1.0, 2.0};

  REQUIRE(plot.vert_lines() == expected);

  crombie2::PlotModel model2 {};

  model2.load(model.save());

  const auto& plot2 = model2.list.front();

  REQUIRE(plot2.name.get() == "test");
  REQUIRE(plot2.vert_lines() == expected);

}
