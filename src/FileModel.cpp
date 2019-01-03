#include <crombie2/FileModel.h>


using namespace crombie2;


std::string FileModel::get_name () const {
  return "files";
}


FileGroup& FileModel::add_files () {
  return filegroups.emplace_back();
}


void FileModel::read (const Types::strings& config) {

}


std::list<std::string> FileModel::serialize () const {

}
