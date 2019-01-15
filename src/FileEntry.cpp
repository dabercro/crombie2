#include <crombie2/FileEntry.h>
#include <crombie2/FileSystem.h>


using namespace crombie2;


FileEntry::FileEntry (const FileEntry& other) :
  name {other.name},
  xs {other.xs} {}


Types::strings& FileEntry::files (const std::string& inputdir) {

  if (last_global == inputdir)
    return files_cache;

  last_global = inputdir;

  auto entry = name.get();

  auto single = entry + ".root";
  if (FileSystem::exists(last_global + "/" + single))
    files_cache.push_back(single);

  else
    files_cache = FileSystem::list(last_global + "/" + entry);

  return files_cache;

}
