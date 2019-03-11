#ifndef CROMBIE2_FILEMODEL_H
#define CROMBIE2_FILEMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/FileGroup.h>


namespace crombie2 {
  /**
     @brief A ConfigModel that holds all of the files to be read
  */
  class FileModel : public ConfigModel {
  public:

    std::string get_name () const override;

    RemoveWrapper<FileGroup>& add_files (FileGroup::FileType type = FileGroup::FileType::DATA);

    RemoveList<FileGroup> filegroups {};

    /**
       @param inputdir Is the directory that should prefix the names of the constituent FileEntry objects
       @returns The total number of files that this object currently refers to
    */
    unsigned num_files (const std::string& inputdir);

    /// Converts FileGroup::FileType enums to strings for serialization
    static const std::map<FileGroup::FileType, std::string> type_to_str;

    /// Converts strings to FileGroup::FileType enums for reading
    static const std::map<std::string, FileGroup::FileType> str_to_type;

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  };
}


#endif
