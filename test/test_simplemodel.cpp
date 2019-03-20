#include "catch.hpp"
#include "utils.h"

#include <crombie2/BoolConfigurable.h>
#include <crombie2/SimpleModel.h>

namespace {
  class TestSimpleModel : public crombie2::SimpleModel {
  public:
    TestSimpleModel () :
      SimpleModel {
      &test
        } {}

    std::string get_name () const override { return "testsimple"; }

    crombie2::BoolConfigurable test {"Test"};

  };
}


TEST_CASE("Test Simple Model Bool") {

  test_dir("testsimple");

  TestSimpleModel model {};

  REQUIRE(bool(model.test) == false);

  model.test.set("1");

  REQUIRE(bool(model.test) == true);

  auto filename = model.save();

  TestSimpleModel model2 {};

  model2.load(filename);

  REQUIRE(bool(model2.test) == true);

}
