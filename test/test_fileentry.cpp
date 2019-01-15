#include "catch.hpp"
#include "utils.h"

#include <fstream>

#include <crombie2/FileEntry.h>
#include <crombie2/FileSystem.h>
#include <crombie2/GlobalModel.h>


TEST_CASE("Test File Entries") {

  std::vector<std::string> dirnames {
    "test",
    "data",
    "mc"
  };

  std::vector<std::string> rootfiles {
    "001.root", "002.root", "003.root"
  };

  auto dir = test_dir("fileentry");

  for (auto& basedir : dirnames) {
    crombie2::FileSystem::mkdirs(dir + "/" + basedir);
    for (auto& file : rootfiles) {
      std::ofstream output {dir + "/" + basedir + "/" + file};
      output << '\n';
    }
  }

  crombie2::GlobalModel model {};
  crombie2::FileEntry entry {};

  model.inputdir.set(dir);

  for (auto& basedir : dirnames) {
    entry.name.set(basedir);
    REQUIRE(entry.files(model.inputdir).size() == rootfiles.size());
  }

}
