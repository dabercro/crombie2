#include <fstream>

#include "crombie2/ConfigModel.h"

namespace crombie2 {
  class TestConfig : public ConfigModel {

  public:

    TestConfig (std::string info = "") : info {info} {}

    std::string get_name () override { return "test"; }

    void read (const Types::strings& config) override {
      info = config.front();
    }

    std::string get () { return info; }

  protected:

    std::list<std::string> serialize () override {
      std::list<std::string> output = {{info}};
      return output;
    }

  private:

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
  two.save_tag("tag");
  three.load_tag("tag");

  REQUIRE(one.get() == three.get());

}
