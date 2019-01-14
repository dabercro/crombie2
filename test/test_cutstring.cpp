#include "catch.hpp"
#include "utils.h"


#include <crombie2/CutModel.h>


TEST_CASE ("Cutstring Expansions") {

  test_dir("cutstring");

  crombie2::CutModel cutmodel {};

  auto& masswindow = cutmodel.add_cutstring("masswindow");

  masswindow.add_cut().set("'60 < h_m'");
  masswindow.add_cut().set("'160 > h_m'");

  auto& test = cutmodel.add_cutstring("test");
  test.add_cut().set("'jet1pt > 40'");

  SECTION ("Mass Selection") {

    test.add_cut().set("masswindow");
    REQUIRE (cutmodel.expand("test") == "(jet1pt > 40 && (60 < h_m && 160 > h_m))");

  }

  SECTION ("Mass Veto") {

    test.add_cut().set("!masswindow");
    REQUIRE (cutmodel.expand("test") == "(jet1pt > 40 && !(60 < h_m && 160 > h_m))");

  }

}
