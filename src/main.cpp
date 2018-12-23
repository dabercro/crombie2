#include <gtkmm/main.h>

#include <crombie2/MainWindow.h>

int main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  crombie2::MainWindow window;
  //Shows the window and returns when it is closed.
  Gtk::Main::run(window);

  return 0;
}
