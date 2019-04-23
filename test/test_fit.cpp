#include "catch.hpp"

#include <crombie2/FitConfig.h>

TEST_CASE ("Creating Fit Config") {

  crombie2::FitConfig fit {"[0] * x^2 + [1] * x + [2]"};

  REQUIRE (fit.guesses.size() == 3);

}
