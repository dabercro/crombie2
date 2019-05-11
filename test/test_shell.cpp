#include "catch.hpp"

#include <crombie2/Misc.h>


TEST_CASE ("Shell command with newlines") {

  REQUIRE(crombie2::Misc::split(crombie2::Misc::shell("printf 'test\ntest\n'"), "\n") == std::vector<std::string>{"test", "test"});

}


TEST_CASE ("Uncertainties") {

  // Branch list, expression, uncertainty, direction
  REQUIRE(crombie2::Misc::uncertify({"jetpt", "jetpt_uncUp", "jetpt_uncDown", "test"},
                                    "jetpt > 60 && test == 3",
                                    "unc", crombie2::Misc::uncdir::UP) == "jetpt_uncUp > 60 && test == 3");

  REQUIRE(crombie2::Misc::uncertify({"jetpt", "jetpt_uncUp", "jetpt_uncDown", "test"},
                                    "jetpt > 60 && test == 3",
                                    "unc", crombie2::Misc::uncdir::DOWN) == "jetpt_uncDown > 60 && test == 3");

  REQUIRE(crombie2::Misc::uncertify({"jetpt", "jetpt_uncUp", "jetpt_uncDown", "test"},
                                    "jetpt > 60 && test == 3",
                                    "test", crombie2::Misc::uncdir::UP) == "jetpt > 60 && test == 3");

  REQUIRE(crombie2::Misc::uncertify({"jetpt", "jetpt1", "jetpt1_uncUp", "jetpt1_uncDown", "test"},
                                    "jetpt > 60 && test == 3",
                                    "test", crombie2::Misc::uncdir::DOWN) == "jetpt > 60 && test == 3");


  REQUIRE(crombie2::Misc::uncertify({"jetpt1", "jetpt1_uncUp", "jetpt1_uncDown", "jetpt2", "jetpt2_uncUp", "jetpt2_uncDown"},
                                    "jetpt1 > 60 && jetpt2 > 30",
                                    "unc", crombie2::Misc::uncdir::DOWN) == "jetpt1_uncDown > 60 && jetpt2_uncDown > 30");

}
