#ifndef CROMBIE2_FILEGROUP_H
#define CROMBIE2_FILEGROUP_H


#include <crombie2/LegendEntry.h>
#include <crombie2/FileEntry.h>
#include <crombie2/RemoveList.h>


namespace crombie2 {
  class FileGroup {
  public:
    enum class FileType {
      DATA,
      MC,
      SIGNAL
    };

    FileType type {FileType::DATA};

    RemoveList<LegendEntry> entries {};
    RemoveList<FileEntry> files {};

  };
}

#endif
