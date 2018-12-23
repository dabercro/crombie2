#include "catch.hpp"

#include <iostream>
#include <sstream>

#include <crombie2/Types.h>
#include <crombie2/Misc.h>
#include <crombie2/Parse.h>

namespace {
  crombie2::Types::strings parse (const std::initializer_list<std::string>& input) {
    std::stringstream stream;
    for (auto& line : input)
      stream << line << std::endl;
    return crombie2::Parse::parse(stream);
  }
}

TEST_CASE("Parser") {

  REQUIRE(parse({"! This is a comment", "", "Not comment"}) ==
          parse({"Not comment"}));

  REQUIRE(parse({"! Comment only"}) == parse({}));

  REQUIRE(parse({"`printf 'Simple shell'`", "`echo 'Complex shell' | perl -ae 'chomp; print'`"}) ==
          parse({"Simple shell", "Complex shell"}));

  REQUIRE(parse({"$ = 1 ; a b", "@ = 2 ;@ c d"}) ==
          parse({"a = 1", "b = 1", "c = 2", "d = 2"}));

  REQUIRE(parse({"$@ = @ ; a b ;@ 1 2"}) ==
          parse({"a1 = 1", "b1 = 1", "a2 = 2", "b2 = 2"}));

  REQUIRE(parse({"env{USER:dabercro}"}) ==
          parse({crombie2::Misc::env("USER", "dabercro")}));

  REQUIRE(parse({"env{NoWaYtHiSaLrEaDyExIsTs:fake}"}) ==
          parse({"fake"}));

}
