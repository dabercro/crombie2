#include <crombie2/FileEntry.h>
#include <crombie2/FileSystem.h>


using namespace crombie2;


const Types::strings& FileEntry::files (const GlobalModel& globalmodel) {

  if (last_global == globalmodel.inputdir.get())
    return files_cache;

  last_global = globalmodel.inputdir;

  auto entry = name.get();

  auto single = entry + ".root";
  if (FileSystem::exists(last_global + "/" + single))
    files_cache.push_back(single);

  else
    files_cache = FileSystem::list(last_global + "/" + entry);

  return files_cache;

}
