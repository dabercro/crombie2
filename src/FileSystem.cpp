#include <cstring>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>


#include <crombie2/FileSystem.h>
#include <crombie2/Misc.h>


using namespace crombie2;


namespace {
  // Is the path for xrd
  bool is_xrd(const std::string& path) {
    return path.find("root://") == 0;
  }

  // Do the xrdfs call
  Types::strings xrd_ls(const std::string& path) {
    // Cache for listed directories to prevent too many calls
    static Types::map<Types::strings> xrd_dir_contents;

    auto iter = xrd_dir_contents.find(path);
    if (iter != xrd_dir_contents.end())
      return iter->second;

    // Door will be between two "//" sequences when user is sane
    auto parts = Misc::split(path, "//");
    if (parts.size() != 3)
      throw std::runtime_error{std::string("xrd path (") + path + ") doesn't seem to have a good pattern"};

    // Set the cache to the split long listing of xrdfs and return it
    return xrd_dir_contents[path] = 
      Misc::split(Misc::shell(std::string("xrdfs root://") + parts[1] + "/ ls -l /" + parts[2] + " | sort -u"));
  }

  // Get the xrd_ls call and return the file portion of the line
  Types::strings xrd_list(const std::string& path) {
    return Misc::comprehension<std::string>(
      xrd_ls(path), [] (auto& line) { return FileSystem::basename(Misc::tokenize(line)[4]); }
    );
  }

  // Get the listing of the directory, and then extract the size
  unsigned long xrd_get_size(const std::string& name) {
    // There is some tricky business about the "//" in ls outputs, so just look for the file
    std::string filename = FileSystem::basename(name);
    for (auto& line : xrd_ls(FileSystem::dirname(name))) {
      if (line.find(filename) != std::string::npos)
        return std::stoul(Misc::tokenize(line)[3]);
    }
    return 0;
  }

  // Hacky way to see if path is there
  bool xrd_exists(const std::string& path) {
    return xrd_get_size(path);
  }

}


std::string FileSystem::basename(const std::string& name) {
  auto output = Misc::split(name, "/").back();
  return output;
}


std::string FileSystem::dirname(const std::string& name) {
  std::string modname = name;
  while (modname.back() == '/')
    modname.pop_back();

  auto output = modname.substr(0, modname.size() - FileSystem::basename(modname).size());
  return output;
}


bool FileSystem::exists(const std::string& path) {
  if (is_xrd(path))
    return xrd_exists(path);
  struct stat buffer;
  return stat(path.data(), &buffer) == 0;
}


unsigned long FileSystem::get_size(const std::string& name) {
  if (is_xrd(name))
    return xrd_get_size(name);
  struct stat file_stat;
  stat(name.data(), &file_stat);
  return file_stat.st_size;
}


void FileSystem::mkdirs(const std::string& path) {
  char path_array[512];
  // Stick a slash on the end to trick our character flipping
  auto addslash = path;
  if (addslash.back() != '/')
    addslash += '/';

  std::strcpy(path_array, addslash.data());
  auto num_chars = std::strlen(path_array);

  for (unsigned i_char = 1; i_char < num_chars; i_char++) {

    if (path_array[i_char] != '/')
      continue;

    // Flip character to null
    path_array[i_char] = '\0';
    if (!exists(path_array)) {
      std::cout << "Making: " << path_array << std::endl;
      mkdir(path_array, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    }
    // Flip back
    path_array[i_char] = '/';
  }
}


Types::strings FileSystem::list(std::string directory) {
  if (is_xrd(directory))
    return xrd_list(directory);

  Types::strings output;

  auto* indir = opendir(directory.data());
  while (auto* dir_ent = readdir(indir)) {
    if (dir_ent->d_name[0] != '.')
      output.emplace_back(dir_ent->d_name);
  }
  closedir(indir);

  return output;
}


bool FileSystem::confirm_overwrite(const std::string& path) {
  if (exists(path)) {
    std::string response;
    std::cout << path << " already exists. Want to overwrite? (y/N)" << std::endl;
    std::getline(std::cin, response);
    return response == "y";
  }
  return true;
}
