#ifndef CROMBIE2_FILESYSTEM_H
#define CROMBIE2_FILESYSTEM_H

#include <crombie2/Types.h>

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

    /**
       @brief Get the contents of a directory

       @param directory The full or relative (from directory where program is run from) path
       @param shouldexist Can be set to false if it's possible for a directory to not exist.
                          If true, displays an error message to the user.
       @returns The name of files inside of the directory, relative to the directory.
                It's an empty vector if the directory does not exist
    */
    Types::strings list(std::string directory, bool shouldexist = true);


    /**
       @brief Confirm overwrite of file or directory.

       @param path Full or relative path of file or directory for message
       @returns This returns whether or not the user confirms the file to be removed.
                If the file doesn't exist, no prompt is generated, and true is returned.
    */
    bool confirm_overwrite(const std::string& path);

  }
}


#endif
