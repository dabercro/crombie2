#ifndef CROMBIE2_FILEMODEL_H
#define CROMBIE2_FILEMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/FileGroup.h>


namespace crombie2 {
  class FileModel : public ConfigModel {
  public:

    std::string get_name () const override;

    FileGroup& add_files ();

    std::list<FileGroup> filegroups {};

  private:

    void read (const Types::strings& config) override;

    std::list<std::string> serialize () const override;

  };
}


#endif
