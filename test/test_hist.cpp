#include "catch.hpp"

#include <crombie2/Hist.h>

TEST_CASE("Filling Hist and Integral") {

  crombie2::Hist hist1 ("", 2, -1, 1);

  hist1.fill(-0.5, 0.5);
  hist1.fill(0.5);
  hist1.fill(2);

  REQUIRE(hist1.integral() == 1.5);
  REQUIRE(hist1.integral(true) == 2.5);

}
