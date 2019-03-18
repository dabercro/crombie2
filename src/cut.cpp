#include <iostream>

#include <gtkmm/main.h>

#include <crombie2/CutModel.h>
#include <crombie2/FileSystem.h>

using namespace crombie2;

int main(int argc, char* argv[]) {

  if (argc != 3 or not FileSystem::exists(argv[1])) {
    std::cout << "Usage: " << argv[0] << " CONFIG SELECTION" << std::endl;
    return 1;
  }

  Gtk::Main kit(argc, argv);

  CutModel model {};
  model.load(argv[1]);

  std::cout << model.expand(argv[2]) << std::endl;

  return 0;

}
