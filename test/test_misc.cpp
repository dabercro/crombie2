#include "catch.hpp"

#include <crombie2/Misc.h>

TEST_CASE ("Test Comprehension") {

  auto test = crombie2::Misc::comprehension
    <int>(std::vector<std::string>({"test", "test"}), [] (auto& ele) { return 0; });

  REQUIRE(test.size() == 2);
  REQUIRE(test[0] == 0);

}


TEST_CASE ("Test nminus1 escape") {

  REQUIRE(crombie2::Misc::nminus1("test[jet]", "test[jet] > 1 && yo") == "(1) && yo");
  REQUIRE(crombie2::Misc::nminus1("hi + world", "hi + world > 1 && yo") == "(1) && yo");

}
