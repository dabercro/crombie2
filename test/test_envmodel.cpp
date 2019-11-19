#include "catch.hpp"
#include "utils.h"

#include <crombie2/EnvelopeModel.h>

TEST_CASE("Envelope Model Saving") {

  test_dir("envmodel");

  crombie2::EnvelopeModel model1 {};

  auto& first = model1.add_cutstring("test1");
  first.add_cut().set("test1_0");
  first.add_cut().set("test1_1");

  auto& second = model1.add_cutstring("test2");
  second.joiner.set("1");
  second.add_cut().set("second");

  crombie2::EnvelopeModel model2 {};

  model2.load(model1.save());

  REQUIRE(model2.list.size() == 2);

  REQUIRE(model2.list.front().name.get() == "test1");

  REQUIRE(not model2.list.front().joiner);

  REQUIRE(model2.list.front().get_cuts().size() == 2);

  REQUIRE(model2.list.back().joiner);
  REQUIRE(model2.list.back().get_cuts().front().get() == "second");

}
