#include <crombie2/FileEntry.h>
#include <crombie2/FileSystem.h>


using namespace crombie2;


const Types::strings& FileEntry::files () {

  if (files_cache.size())
    return files_cache;

  auto entry = name.get();

  auto single = entry + ".root";
  if (FileSystem::exists(single))
    files_cache.push_back(single);

  else
    files_cache = FileSystem::list(entry);

  return files_cache;

}
