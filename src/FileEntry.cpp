#include <crombie2/FileEntry.h>
#include <crombie2/FileSystem.h>
#include <crombie2/Misc.h>


using namespace crombie2;


FileEntry::FileEntry (const FileEntry& other) :
  name {other.name},
  xs {other.xs} {}


Types::strings FileEntry::files (const std::string& inputdir) const {

  Types::strings output {};

  auto entry = name.get();

  auto single = entry + ".root";
  if (FileSystem::exists(inputdir + "/" + single))
    output.push_back(single);

  else {
    entry += '/';
    output = Misc::comprehension<std::string>
      (FileSystem::list(inputdir + "/" + entry, true, false),
       [&entry] (auto& ele) { return entry + ele; });
  }

  return output;

}
