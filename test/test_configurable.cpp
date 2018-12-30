#include "catch.hpp"

#include <crombie2/Configurable.h>
#include <crombie2/Cut.h>

TEST_CASE("Configurables") {

  crombie2::Configurable<std::string> conf ("Label", "value");
  REQUIRE(conf.get() == "value");
  REQUIRE(conf.label() == "Label");

  conf.set("new value");
  REQUIRE(conf.get() == "new value");

  crombie2::Configurable<int> intconf ("Label", 3);
  REQUIRE(intconf.get() == "3");
  intconf.set("523");
  REQUIRE(intconf.get() == "523");

}

TEST_CASE("Cut") {
  crombie2::Cut cut {"'jetpt < 60'"};

  REQUIRE(cut.get() == "'jetpt < 60'");
  REQUIRE(cut.cut() == "jetpt < 60");
  REQUIRE(cut.label() == "jetpt");
  REQUIRE(cut.is_literal() == true);

  cut.set("subexpr");

  REQUIRE(cut.is_literal() == false);
  REQUIRE(cut.get() == "subexpr");
  REQUIRE(cut.label() == "SUB");

}
