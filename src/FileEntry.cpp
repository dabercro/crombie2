#include <crombie2/FileEntry.h>
#include <crombie2/FileSystem.h>
#include <crombie2/Misc.h>


using namespace crombie2;


FileEntry::FileEntry (const FileEntry& other) :
  name {other.name},
  xs {other.xs} {}


Types::strings& FileEntry::files (const std::string& inputdir) {

  if (last_listing == inputdir)
    return files_cache;

  auto entry = name.get();

  last_listing = inputdir + "/" + entry;

  auto single = entry + ".root";
  if (FileSystem::exists(inputdir + "/" + single))
    files_cache.push_back(single);

  else {
    entry += '/';
    files_cache = Misc::comprehension<std::string>
      (FileSystem::list(last_listing),
       [&entry] (auto& ele) { return entry + ele; });
  }

  return files_cache;

}
