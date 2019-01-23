#ifndef CROMBIE2_FILEENTRY_H
#define CROMBIE2_FILEENTRY_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>
#include <crombie2/Types.h>


namespace crombie2 {
  /**
     @brief Part of the FileModel that lists a specific directory or file containing a physics process
  */
  class FileEntry {
  public:
    FileEntry () = default;
    FileEntry (const FileEntry& other);

    Configurable<std::string> name {"File Name", ""};
    Configurable<double> xs {"Cross Section", 0};
    ConfigTable table {{
      &name, &xs
    }, true};

    /**
       Get the full list of files
    */
    Types::strings& files (const std::string& inputdir);

  private:
    std::string last_listing {};    ///< Variable that holds the last directory that was listed
    Types::strings files_cache {};  ///< A cache of the last listing results

  };
}


#endif
