#include "utils.h"

std::string test_dir (const std::string& dir) {
  std::string location = std::string(getenv("HOME")) + "/.crombie2/test/" + dir;
  crombie2::ConfigModel::set_config_dir(location);
  return location;
}
