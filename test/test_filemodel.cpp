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

  REQUIRE(model.get_datacard_names(crombie2::FileGroup::FileType::DATA) == std::vector<std::string>{"data_obs"});
  REQUIRE(model.get_datacard_names(crombie2::FileGroup::FileType::MC) == std::vector<std::string>{"zj", "zb", "ttbar"});
  REQUIRE(model.get_datacard_names(crombie2::FileGroup::FileType::SIGNAL) == std::vector<std::string>{});

}


TEST_CASE("Using Scientific Notation") {

  test_dir("filescience");

  crombie2::FileModel model {};

  auto& group = model.add_files(crombie2::FileGroup::FileType::MC);

  auto& entry = group.entries.append();

  entry.datacard.set("mc");
  entry.legend.set("MC");

  // We really want the cross sections

  auto& file = group.files.append();

  file.name.set("filename");
  file.xs.set("1.23e+07");

  REQUIRE(model.filegroups.front().files.front().xs == 1.23e+07);

  crombie2::FileModel model2 {};
  model2.load(model.save());

  REQUIRE(model2.filegroups.front().files.front().xs == 1.23e+07);

}
