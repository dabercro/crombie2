#include "catch.hpp"
#include "utils.h"

#include <fstream>

#include <crombie2/FileEntry.h>
#include <crombie2/FileSystem.h>
#include <crombie2/GlobalModel.h>


TEST_CASE("Test File Entries") {

  auto dir = test_dir("fileentry");

  crombie2::GlobalModel model {};
  crombie2::FileEntry entry {};

  model.inputdir.set(dir);

  SECTION("Multiple Files") {

    std::vector<std::string> dirnames {
      "test",
      "data",
      "mc"
    };

    std::vector<std::string> rootfiles {
      "001.root", "002.root", "003.root"
    };

    for (auto& basedir : dirnames) {
      crombie2::FileSystem::mkdirs(dir + "/" + basedir);
      for (auto& file : rootfiles) {
        std::ofstream output {dir + "/" + basedir + "/" + file};
        output << '\n';
      }
    }

    for (auto& basedir : dirnames) {
      entry.name.set(basedir);
      auto files = entry.files(model.inputdir);
      REQUIRE(files.size() == rootfiles.size());
      REQUIRE(files.front() == basedir + "/001.root");
    }

  }

  SECTION("Single File") {
    {
      std::ofstream output {dir + "/testsingle.root"};
      output << '\n';
    }

    entry.name.set("testsingle");

    REQUIRE(entry.files(model.inputdir) == std::vector<std::string>{"testsingle.root"});

  }

  // We don't want to try to run on empty files.
  // Just don't list them from the beginning!
  SECTION("Empty File") {

    std::string basedir = "empty";
    crombie2::FileSystem::mkdirs(dir + "/" + basedir);

    {
      std::ofstream output {dir + "/" + basedir + "/notempty.root"};
      output << '\n';
      std::ofstream empty {dir + "/" + basedir + "/empty.root"};
    }

    entry.name.set(basedir);
    auto files = entry.files(model.inputdir);

    REQUIRE(files.size() == 1);
    REQUIRE(files[0] == basedir + "/notempty.root");

  }

}
