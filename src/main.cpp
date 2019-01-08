#include <gtkmm/main.h>

#include <crombie2/MainWindow.h>

#include "TROOT.h"

int main (int argc, char *argv[])
{
  ROOT::EnableThreadSafety();

  Gtk::Main kit(argc, argv);

  crombie2::MainWindow window;
  //Shows the window and returns when it is closed.
  Gtk::Main::run(window);

  return 0;
}
