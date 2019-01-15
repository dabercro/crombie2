#include "catch.hpp"

#include <crombie2/Misc.h>

TEST_CASE ("Test Comprehension") {

  auto test = crombie2::Misc::comprehension
    <int>(std::vector<std::string>({"test", "test"}), [] (auto& ele) { return 0; });

  REQUIRE(test.size() == 2);
  REQUIRE(test[0] == 0);

}
