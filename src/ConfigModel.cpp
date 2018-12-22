#include <fstream>
#include <sstream>
#include <functional>

#include "crombie2/FileSystem.h"
#include "crombie2/ConfigModel.h"


void crombie2::ConfigModel::load_tag (const std::string& tag) {

  std::string file_name;

  std::string tag_file_name = config_directory + "/" + get_name() + "/tags/" + tag;

  std::ifstream input {tag_file_name};
  input >> file_name;
  load(file_name);

}


void crombie2::ConfigModel::save (const std::string& file_name) {

  // Make the directory for the output
  crombie2::FileSystem::mkdirs(crombie2::FileSystem::dirname(file_name));

  std::ofstream output {file_name};

  for (auto& line : serialize())
    output << line << std::endl;

}


std::string crombie2::ConfigModel::save () {

  auto hash_val = hash();

  // First two characters are used as a directory, and the rest for the file name
  hash_val.insert(2, "/");

  // Put together full name from config_dictionary and name of the config type
  auto file_name = config_directory + "/" + get_name() + "/" + hash().insert(2, "/");

  save(file_name);

  return file_name;

}


void crombie2::ConfigModel::save_tag (const std::string& tag) {

  auto tag_file_name = config_directory + "/" + get_name() + "/tags/" + tag;

  // Make output directory, just in case
  crombie2::FileSystem::mkdirs(crombie2::FileSystem::dirname(tag_file_name));

  std::ofstream output {tag_file_name};
  output << save() << std::endl;

}


std::string crombie2::ConfigModel::hash () {

  // We'll hold the hash output (long) here to convert to string
  std::stringstream converter;

  // Put the lines into a single string for the hash
  std::string buffer;
  for (auto& line : serialize())
    buffer += line + '\n';

  // Dump the hash into the converter
  converter << std::hash<std::string>()(buffer);

  // Put back into string
  std::string output;
  converter >> output;

  return output;

}


void crombie2::ConfigModel::set_config_dir (const std::string& dir) {
  config_directory = dir;
}


std::string crombie2::ConfigModel::config_directory { std::string(getenv("HOME")) + "/.crombie2" };
