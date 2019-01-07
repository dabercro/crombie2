#ifndef CROMBIE2_FILEENTRY_H
#define CROMBIE2_FILEENTRY_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>
#include <crombie2/GlobalModel.h>


namespace crombie2 {
  class FileEntry {
  public:
    FileEntry () = default;
    FileEntry (const FileEntry& other);

    Configurable<std::string> name {"File Name", ""};
    Configurable<double> xs {"Cross Section", 0};
    ConfigTable table {{
      &name, &xs
    }, true};

    const Types::strings& files (const GlobalModel& globalmodel);

  private:
    std::string last_global {};
    Types::strings files_cache {};

  };
}


#endif
