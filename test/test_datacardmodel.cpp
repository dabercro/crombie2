#include "catch.hpp"
#include "utils.h"


#include <crombie2/DatacardModel.h>


TEST_CASE("Datacard Model validity") {

  test_dir("filemodel");

  crombie2::DatacardModel data {};
  crombie2::PlotModel plots {};
  crombie2::CutModel cuts {};

  REQUIRE(data.is_valid(cuts, plots, true) == true);

  auto& hist = data.hists.append();
  hist.selection.set("select");
  hist.plot.set("plot");

  REQUIRE(data.is_valid(cuts, plots, true) == false);

  plots.add().name.set("plot");
  cuts.add_cutstring("select").add_cut().set("'1'");

  REQUIRE(data.is_valid(cuts, plots, true) == true);

}
