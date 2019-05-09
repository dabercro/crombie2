#include "catch.hpp"
#include "utils.h"


#include <crombie2/FileModel.h>


TEST_CASE("Test File Model legend to datacard") {

  test_dir("filemodel");

  crombie2::FileModel model {};

  auto add_entry = [] (auto& group, std::string data, std::string legend) {

    auto& entry = group.entries.append();

    entry.datacard.set(data);
    entry.legend.set(legend);

  };

  add_entry(model.add_files(), "data_obs", "Data");

  auto& mcgroup = model.add_files(crombie2::FileGroup::FileType::MC);

  add_entry(mcgroup, "zj", "Z + light");
  add_entry(mcgroup, "zb", "Z + heavy");

  add_entry(model.add_files(crombie2::FileGroup::FileType::MC), "ttbar", "TT");

  REQUIRE(model.filegroups.size() == 3);
  REQUIRE(model.get_datacard_name("Z + light") == "zj");
  REQUIRE(model.get_datacard_name("Z + heavy") == "zb");
  REQUIRE(model.get_datacard_name("Data") == "data_obs");
  REQUIRE(model.get_datacard_name("TT") == "ttbar");

}
