#include "crombie2/ConfigModel.h"

void test_dir (const std::string& dir) {
  crombie2::ConfigModel::set_config_dir(std::string(getenv("HOME")) + "/.crombie2/test/" + dir);
}
