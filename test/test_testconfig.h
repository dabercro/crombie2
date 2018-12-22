#include "crombie2/ConfigModel.h"

#include <fstream>

namespace crombie2 {
  class TestConfig : public ConfigModel {

  public:

    TestConfig (std::string info = "") : info {info} {}

    std::string get_name () override { return "test"; }

    void load (const std::string& file_name) override {
      std::ifstream input {file_name};
      input >> info;
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

  crombie2::ConfigModel::set_config_dir("test/testconfig");

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
