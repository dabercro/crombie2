#include <crombie2/FileSystem.h>
#include <crombie2/Job.h>


using namespace crombie2;


Job::Job (const GlobalModel& globalmodel,
          FileGroup& group,
          FileEntry& entry,
          const std::string& file) :
  globalmodel {globalmodel},
  group {group},
  entry {entry},
  file_name {globalmodel.inputdir.get() + "/" + entry.name.get() + "/" + file},
  size {FileSystem::get_size(globalmodel.inputdir.get() + "/" + entry.name.get() + "/" + file)} {}


void Job::add_analyzer (Analyzer* analyzer) {

  analyzers.push_back(analyzer);

}


void Job::run () {

  if (not analyzers.size())
    return;

  Tree tree {file_name, globalmodel.tree.get()};

  for (auto* analyzer : analyzers)
    analyzer->make_requests(tree);

  while (tree.next()) {
    for (auto* analyzer : analyzers)
      analyzer->notify();
  }

}


const FileGroup& Job::get_group () const {
  return group;
}


const FileEntry& Job::get_entry () const {
  return entry;
}


const std::string& Job::get_file_name () const {
  return file_name;
}
