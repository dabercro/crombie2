#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "test_dir.h" // Keep this at the top so all other tests have access to it

#include "test_testconfig.h"
#include "test_parser.h"
#include "test_configurable.h"

TEST_CASE("Example") {
  REQUIRE(10 == 5 + 5);
}
