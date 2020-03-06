#include "catch.hpp"
#include "utils.h"


#include <crombie2/CutModel.h>
#include <crombie2/Misc.h>


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
    REQUIRE (cutmodel.cutflow("test") == crombie2::Types::strings{"jet1pt > 40", "60 < h_m", "160 > h_m"});

  }

  SECTION ("Mass Veto") {

    test.add_cut().set("!masswindow");
    REQUIRE (cutmodel.expand("test") == "(jet1pt > 40 && !(60 < h_m && 160 > h_m))");
    REQUIRE (cutmodel.cutflow("test") == crombie2::Types::strings{"jet1pt > 40", "!(60 < h_m && 160 > h_m)"});

  }

  SECTION ("Blank Cut") {

    test.add_cut();
    REQUIRE (cutmodel.expand("test") == "(jet1pt > 40)");
    REQUIRE (cutmodel.cutflow("test") == crombie2::Types::strings{"jet1pt > 40"});

  }

  SECTION ("Infinite Recursion ") {
    test.add_cut().set("test");
    cutmodel.add_cutstring("unity").add_cut().set("'1'");

    cutmodel.selections.append("test", "unity", "unity");

    REQUIRE (cutmodel.is_valid() == false);

  }

}


TEST_CASE ("Nminus1") {

  REQUIRE (crombie2::Misc::nminus1("jet1pt", "(jet1pt > 60 && jet2pt < 30)") == "((1) && jet2pt < 30)");
  // Put the variable on the right side to avoid taking it out
  REQUIRE (crombie2::Misc::nminus1("jet1pt", "(60 < jet1pt && jet2pt < 30)") == "(60 < jet1pt && jet2pt < 30)");

}


TEST_CASE ("Selection") {
  test_dir("selection");

  crombie2::CutModel cutmodel {};

  cutmodel.add_cutstring("jetpt").add_cut().set("'jetpt > 60'");
  cutmodel.add_cutstring("unity").add_cut().set("'1'");

  cutmodel.selections.append("jetpt", "unity", "unity", "", "plotname");

  std::string tag = "selection_test";

  cutmodel.save_tag(tag, true);

  crombie2::CutModel cutmodel2 {};

  cutmodel2.load_tag(tag);

  auto& sel1 = cutmodel.selections.front();
  auto& sel2 = cutmodel2.selections.front();

  REQUIRE (sel1.name.get() == sel2.name.get());
  REQUIRE (sel1.control_plot.get() == sel2.control_plot.get());

}


TEST_CASE ("Empty") {

  test_dir("emptycut");

  crombie2::CutModel cutmodel {};
  cutmodel.add_cutstring("unity").add_cut().set("'1'");

  REQUIRE (cutmodel.expand("unity") == "(1)");

}


TEST_CASE ("Labels") {

  test_dir("labels");

  crombie2::CutModel cutmodel {};
  auto& cutstring = cutmodel.add_cutstring("jetpt");
  cutstring.add_cut().set("'jetpt > 60'");
  cutstring.label.set("p_T > 60 [GeV]");

  auto& unity = cutmodel.add_cutstring("unity");
  unity.add_cut().set("'1'");

  std::string tag = "label_test";

  cutmodel.selections.append("jetpt", "unity", "unity", "", "plotname");

  cutmodel.save_tag(tag, true);

  crombie2::CutModel cutmodel2 {};

  cutmodel2.load_tag(tag);

  REQUIRE(cutmodel.labels("jetpt").size() == 1);
  REQUIRE(cutmodel.labels("jetpt").front() == "p_T > 60 [GeV]");
  REQUIRE(cutmodel.labels("jetpt") == cutmodel2.labels("jetpt"));

  unity.label.set("unity");
  cutstring.add_cut().set("unity");

  REQUIRE(cutmodel.labels("jetpt").size() == 2);
  REQUIRE(cutmodel.labels("jetpt").back() == "unity");

  crombie2::CutModel cutmodel3 {};
  cutmodel3.load(cutmodel.save());

  REQUIRE(cutmodel.labels("jetpt") == cutmodel3.labels("jetpt"));

  auto& notunity = cutmodel2.add_cutstring("notunity");
  notunity.add_cut().set("'0'");

  notunity.label.set("not unity");
  cutmodel2.get_cutstring("jetpt").add_cut().set("!notunity");

  REQUIRE(cutmodel2.labels("jetpt").size() == 1);

}
