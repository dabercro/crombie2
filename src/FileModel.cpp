#include <regex>
#include <exception>

#include <crombie2/FileModel.h>


using namespace crombie2;


std::string FileModel::get_name () const {
  return "files";
}


FileGroup& FileModel::add_files (FileGroup::FileType type) {
  auto& output = filegroups.emplace_back();
  output.type = type;
  return output;
}


void FileModel::read (const Types::strings& config) {
  FileGroup::FileType current_type {FileGroup::FileType::DATA};

  // Not pointing to a legend entry list in the beginning
  std::list<LegendEntry>* current_entries {nullptr};
  std::list<FileEntry>* current_files {nullptr};

  std::regex legend_expr {"\\s*(.+);\\s*(.+);\\s*(.+);\\s*(\\d+)"};
  std::regex file_expr {"\\s*(\\S+)\\s+\\{([\\d\\.]+)\\}"};
  std::smatch matches;

  for (auto& line : config) {
    if (std::regex_match(line, matches, legend_expr)) {
      if (not current_entries) {
        auto& fg = add_files(current_type);
        current_entries = &(fg.entries);
        current_files = &(fg.files);
      }

      auto& entry = current_entries->emplace_back();
      entry.datacard.set(matches[1]);
      entry.legend.set(matches[2]);
      entry.cut.set(matches[3]);
      entry.style.set(matches[4]);

    }

    else if (std::regex_match(line, matches, file_expr)) {
      if (not current_files)
        throw std::logic_error{"Input file makes no sense"};

      auto& file = current_files->emplace_back();
      file.name.set(matches[1]);
      file.xs.set(matches[2]);

    }

    else
      current_type = str_to_type.at(line);

    // No other line type is valid

  }

}


std::list<std::string> FileModel::serialize () const {
  std::list<std::string> output {};

  for (auto& filegroup : filegroups) {
    if (output.size())
      output.emplace_back();

    output.emplace_back(type_to_str.at(filegroup.type));
    output.emplace_back();

    for (auto& legend : filegroup.entries) {
      if (legend.datacard.get().size())
        output.emplace_back(legend.datacard.get() + "; " +
                            legend.legend.get() + "; " +
                            legend.cut.get() + "; " +
                            legend.style.get());
    }
    
    output.emplace_back();

    for (auto& file : filegroup.files) {
      if (file.name.get().size())
        output.emplace_back(file.name.get() + " {" + file.xs.get() + "}");
    }

  }

  return output;

}


const std::map<FileGroup::FileType, std::string> FileModel::type_to_str {
  {FileGroup::FileType::DATA, "DATA"},
  {FileGroup::FileType::MC, "MC"},
  {FileGroup::FileType::SIGNAL, "SIGNAL"}
};


const std::map<std::string, FileGroup::FileType> FileModel::str_to_type {
  {"DATA", FileGroup::FileType::DATA},
  {"MC", FileGroup::FileType::MC},
  {"SIGNAL", FileGroup::FileType::SIGNAL}
};