#ifndef CROMBIE2_FILESYSTEM_H
#define CROMBIE2_FILESYSTEM_H

#include <crombie2/Misc.h>

namespace crombie2 {
  namespace FileSystem {

    std::string basename(const std::string& name);

    std::string dirname(const std::string& name);

    /// Check if path exists (either directory or file)
    bool exists(const std::string& path);

    /// Get the size of a file
    unsigned long get_size(const std::string& name);

    /// Create directories, recursively if needed
    void mkdirs(const std::string& path);

    /// The name of files inside of the directory
    Types::strings list(std::string directory);


    /**
       If this would overwrite a directory that exists, ask for confirmation.
       This returns whether or not the user confirms the file to be removed.
    */
    bool confirm_overwrite(const std::string& path);

  }
}


#endif
