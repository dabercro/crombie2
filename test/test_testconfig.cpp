#include "catch.hpp"
#include "utils.h"

#include <fstream>

#include <crombie2/ConfigModel.h>

namespace crombie2 {
  class TestConfig : public ConfigModel {

  public:

    TestConfig (std::string info = "") : info {info} {}

    std::string get_name () const override { return "test"; }

    std::string get () { return info; }

  private:

    void read (const Types::strings& config) override {
      info = config.front();
    }

    std::list<std::string> serialize () const override {
      std::list<std::string> output = {{info}};
      return output;
    }

    std::string info;

  };
}

TEST_CASE("TestConfig object") {

  test_dir("testconfig");

  crombie2::TestConfig one {"test"};
  crombie2::TestConfig two {"aa"};

  REQUIRE(one.get() > two.get());

  two.load(one.save());

  REQUIRE(one.get() == two.get());

  crombie2::TestConfig three {};
  two.save_tag("tag", true);
  three.load_tag("tag");

  REQUIRE(one.get() == three.get());

}
