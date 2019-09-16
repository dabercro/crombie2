#include <regex>
#include <exception>

#include <crombie2/FileModel.h>
#include <crombie2/FileSystem.h>
#include <crombie2/Misc.h>


using namespace crombie2;


std::string FileModel::get_name () const {
  return "files";
}


RemoveWrapper<FileGroup>& FileModel::add_files (FileGroup::FileType type) {
  auto& output = filegroups.append();
  output.type = type;
  return output;
}


unsigned FileModel::num_files (const std::string& inputdir) {

  unsigned output {0};
  for (auto& group : filegroups) {
    for (auto& entry : group.files)
      output += entry.files(inputdir).size();

  }
  return output;

}


void FileModel::read (const Types::strings& config) {
  filegroups.clear();

  FileGroup::FileType current_type {FileGroup::FileType::DATA};

  // Not pointing to a legend entry list in the beginning
  RemoveList<LegendEntry>* current_entries {nullptr};
  RemoveList<FileEntry>* current_files {nullptr};

  std::regex legend_expr {"\\s*([^;]+);\\s*([^;]+);\\s*([^;]+);\\s*(\\d+)"};
  std::regex file_expr {"\\s*(\\S+)\\s+\\{([\\d\\.]+)\\}"};
  std::smatch matches;

  for (auto& line : config) {
    if (std::regex_match(line, matches, legend_expr)) {
      if (not current_entries) {
        auto& fg = add_files(current_type);
        current_entries = &(fg.entries);
        current_files = &(fg.files);
      }

      auto& entry = current_entries->append();
      entry.datacard.set(matches[1]);
      entry.legend.set(matches[2]);
      entry.cut.set(matches[3]);
      entry.style.set(matches[4]);

    }

    else if (std::regex_match(line, matches, file_expr)) {
      if (not current_files)
        throw std::logic_error{"Input file makes no sense"};

      current_entries = nullptr;

      auto& file = current_files->append();
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

    output.emplace_back();

  }

  if (output.size())
    output.pop_back();

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


std::string FileModel::get_datacard_name (const std::string& legend) const {

  for (auto& group : filegroups) {

    for (auto& entry : group.entries) {
      if (legend == entry.legend.get())
        return entry.datacard.get();
    }

  }

  throw std::logic_error{std::string("Searching for unknown legend ") + legend};

}


std::vector<std::string> FileModel::get_datacard_names (FileGroup::FileType type) const {

  std::vector<std::string> output {};

  for (auto& group : filegroups) {
    if (group.type == type) {
      for (auto& entry : group.entries)
        output.emplace_back(entry.datacard);
    }
  }

  return output;

}


bool FileModel::is_valid (const GlobalModel& globalmodel) const {

  auto inputdir = globalmodel.inputdir.get() + "/";

  for (auto& group : filegroups) {
    for (auto& entry : group.files) {
      auto tryname = inputdir + entry.name.get();
      if (not (FileSystem::exists(tryname) or FileSystem::exists(tryname + ".root"))) {
        Misc::message(tryname + " does not exist!");
        return false;
      }
    }
  }

  // Next check that MC and Data branches match, if both used
  Types::strings mc_branches {};
  Types::strings data_branches {};

  auto getbranches = [&globalmodel] (const auto& entry) {

    Types::strings output {};

    Tree infile {
      globalmodel.inputdir.get() + "/" + entry.files(globalmodel.inputdir).front(),
      globalmodel.tree
    };

    for (auto* branch : *(infile.get<TTree>(globalmodel.tree.get())->GetListOfBranches()))
      output.emplace_back(branch->GetName());

    return output;

  };

  for (auto& group : filegroups) {
    if (group.type == FileGroup::FileType::DATA and not data_branches.size())
      data_branches = getbranches(group.files.front());
    if ((group.type == FileGroup::FileType::MC or group.type == FileGroup::FileType::SIGNAL)
        and not mc_branches.size())
      mc_branches = getbranches(group.files.front());
  }

  // size() == 0 if we're not using both MC and Data
  if (data_branches.size() and mc_branches.size() and data_branches != mc_branches) {
    Misc::message("Data and MC branches do not match!");
    return false;
  }

  return true;

}


Tree FileModel::get_one (const GlobalModel& globalmodel) const {

  auto& entry = filegroups.front().files.front();
  return Tree(globalmodel.inputdir.get() + "/" + entry.files(globalmodel.inputdir).front(),
              globalmodel.tree);

}
