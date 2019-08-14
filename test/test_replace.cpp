#include "catch.hpp"
#include "utils.h"

#include <crombie2/Configurable.h>
#include <crombie2/SimpleModel.h>

namespace {
  class TestSimpleModel : public crombie2::SimpleModel {
  public:
    TestSimpleModel () :
      SimpleModel {
      &test, &test2, &test3
        } {}

    std::string get_name () const override { return "testsimple"; }

    crombie2::Configurable<std::string> test {"test", "jet1_pt"};

    crombie2::Configurable<std::string> test2 {"test2", "jet1_pt; yojet1_eta"};

    crombie2::Configurable<std::string> test3 {"test3", "jet_pt; jet_eta"};

  };
}


TEST_CASE("Test Replace") {

  test_dir("replace");

  TestSimpleModel model {};

  REQUIRE(model.test.get() == "jet1_pt");
  REQUIRE(model.test2.get() == "jet1_pt; yojet1_eta");
  REQUIRE(model.test3.get() == "jet_pt; jet_eta");

  model.replace("jet1", "jet2");

  REQUIRE(model.test.get() == "jet2_pt");
  REQUIRE(model.test2.get() == "jet2_pt; yojet2_eta");
  REQUIRE(model.test3.get() == "jet_pt; jet_eta");

}
