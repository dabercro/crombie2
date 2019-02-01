#include "catch.hpp"

#include <crombie2/LumiSelection.h>


TEST_CASE ("Lumi Selection") {

  crombie2::LumiSelection lumi1 {};

  lumi1.add(123, 4321);
  REQUIRE(lumi1.show() == "{\"123\": [[4321, 4321]]}");

  lumi1.add(123, {789, 987});
  REQUIRE(lumi1.show() == "{\"123\": [[789, 987], [4321, 4321]]}");


  crombie2::LumiSelection lumi2 {};

  lumi2.add(123, {800, 4320});
  lumi2.add(321, {3, 3});

  REQUIRE(lumi2.show() == "{\"123\": [[800, 4320]], \"321\": [[3, 3]]}");

  lumi1.add(lumi2);

  REQUIRE(lumi1.show() == "{\"123\": [[789, 4321]], \"321\": [[3, 3]]}");

}
