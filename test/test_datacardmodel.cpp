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

TEST_CASE("Datacard Model has region, plot") {

  crombie2::DatacardModel data {};
  auto& unc = data.flats.append();

  // Empty means that all signals and processes are valid
  REQUIRE(unc.has_process("proc") == true);
  REQUIRE(unc.has_region("signal") == true);

  unc.regions.set("signal1");

  REQUIRE(unc.has_process("proc") == true);
  REQUIRE(unc.has_region("signal") == false);

  unc.regions.set("signal");
  unc.procs.set("proc");

  REQUIRE(unc.has_process("proc") == true);
  REQUIRE(unc.has_region("signal") == true);

  unc.regions.set("test,signal");
  unc.procs.set("test,proc");

  REQUIRE(unc.has_process("proc") == true);
  REQUIRE(unc.has_region("signal") == true);

  unc.regions.set("test,signal1");
  unc.procs.set("test,proc1");

  REQUIRE(unc.has_process("proc") == false);
  REQUIRE(unc.has_region("signal") == false);

}
