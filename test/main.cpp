#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "test_testconfig.h"

TEST_CASE("Example") {
  REQUIRE(10 == 5 + 5);
}
