#include <fstream>
#include <sstream>
#include <regex>

#include <crombie2/ConfigModel.h>
#include <crombie2/FileSystem.h>
#include <crombie2/Misc.h>
#include <crombie2/Parse.h>


using namespace crombie2;


ConfigModel::ConfigModel (const std::string& file_name) {
  if (file_name.size())
    load(file_name);
}


void ConfigModel::load (const std::string& file_name) {

  if (FileSystem::exists(file_name)) {
    std::ifstream input {file_name};
    read(Parse::parse(input));
  }

}


void ConfigModel::load_tag (const std::string& tag) {

  std::string file_name;

  std::string tag_file_name = config_directory + "/" + get_name() + "/tags/" + tag;

  if (FileSystem::exists(tag_file_name)) {
    std::ifstream input {tag_file_name};
    input >> file_name;
    load(file_name);
  }

}


void ConfigModel::save (const std::string& file_name) {

  // Make the directory for the output
  FileSystem::mkdirs(FileSystem::dirname(file_name));

  std::ofstream output {file_name};

  for (auto& line : serialize())
    output << line << std::endl;

}


std::string ConfigModel::filename () const {

  auto hash_val = hash();

  // First two characters are used as a directory, and the rest for the file name
  hash_val.insert(2, "/");

  // Put together full name from config_dictionary and name of the config type
  auto file_name = config_directory + "/" + get_name() + "/" + hash().insert(2, "/");

  return file_name;

}


std::string ConfigModel::save () {

  auto file_name = filename();

  save(file_name);

  return file_name;

}


std::string ConfigModel::save_tag (const std::string& tag, bool overwrite) {

  if (not is_valid())
    return "";

  auto tag_file_name = config_directory + "/" + get_name() + "/tags/" + tag;

  // Make output directory, just in case
  FileSystem::mkdirs(FileSystem::dirname(tag_file_name));

  if (not overwrite and
      FileSystem::exists(tag_file_name) and
      not Misc::confirm(get_name() + ": replace tag " + tag + "?"))
    return "";

  auto file_name = save();
  std::ofstream output {tag_file_name};
  output << file_name << std::endl;

  return file_name;

}


std::string ConfigModel::hash () const {

  // We'll hold the hash output (long) here to convert to string
  std::stringstream converter;

  // Put the lines into a single string for the hash
  std::string buffer;
  for (auto& line : serialize())
    buffer += line + '\n';

  // Dump the hash into the converter
  converter << std::hex << std::hash<std::string>()(buffer);

  return converter.str();

}


void ConfigModel::set_config_dir (const std::string& dir) {
  config_directory = dir;
}


const std::string& ConfigModel::get_config_dir () {

  return config_directory;

}
  

std::string ConfigModel::config_directory { Misc::env("HOME") + "/.crombie2" };


bool ConfigModel::is_valid () const {

  return true;

}

void ConfigModel::replace (const std::string& target, const std::string& newstr) {

  Types::strings newlines {};

  std::regex expr {target};

  for (auto& line : serialize()) {
    if (line.size())
      newlines.push_back(std::regex_replace(line, expr, newstr));
  }

  read(newlines);

}

