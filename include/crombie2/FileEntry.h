#ifndef CROMBIE2_FILEENTRY_H
#define CROMBIE2_FILEENTRY_H


#include <crombie2/ConfigTable.h>
#include <crombie2/Configurable.h>


namespace crombie2 {
  class FileEntry {
    Configurable<std::string> name {"File Name", ""};
    Configurable<double> xs {"Cross Section", 0};
    ConfigTable<Gtk::HBox> table {
      &name, &xs
    };
  };
}


#endif
