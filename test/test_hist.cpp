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

TEST_CASE("Envelope Adding") {

  crombie2::Hist hist1 ("", 2, -1, 1);

  std::vector<double> contents {2, 2, 2, 2};
  std::vector<double> sumw2 {1, 1, 1, 1};

  crombie2::Hist hist_up ("", 2, -1, 1);
  std::vector<double> slope_up {1, 1.5, 2.5, 3};

  crombie2::Hist hist_down ("", 2, -1, 1);
  std::vector<double> slope_down {3, 2.5, 1.5, 1};

  hist1.set_contents(contents, sumw2);
  hist_up.set_contents(slope_up, sumw2);
  hist_down.set_contents(slope_down, sumw2);

  hist1.add_env("env", hist_up);
  hist1.add_env("env", hist_down);

  SECTION ("Envelope Results") {

    auto minmax = hist1.get_minmax_env("env");

    REQUIRE(minmax.first.get_contents() == std::vector<double>{1, 1.5, 1.5, 1});
    REQUIRE(minmax.second.get_contents() == std::vector<double>{3, 2.5, 2.5, 3});

    REQUIRE(hist1.get_errors() == sumw2);

    hist1.merge_envs("env");
    for (unsigned ibin = 0; ibin < 4; ++ibin)
      REQUIRE(hist1.get_errors()[ibin] > sumw2[ibin]);

    REQUIRE(hist1.get_errors()[0] == 2);
    REQUIRE(hist1.get_errors()[3] == 2);

  }

  SECTION ("Envelope Errors") {

    hist1.set_contents(contents, std::vector<double>(4));

    hist1.merge_envs("env");

    REQUIRE(hist1.get_errors()[0] == 1);
    REQUIRE(hist1.get_errors()[3] == 1);

  }

  SECTION ("Scale") {

    hist1.scale(2);

    auto minmax = hist1.get_minmax_env("env");

    REQUIRE(minmax.first.get_contents() == std::vector<double>{2, 3, 3, 2});
    REQUIRE(minmax.second.get_contents() == std::vector<double>{6, 5, 5, 6});

  }

}
