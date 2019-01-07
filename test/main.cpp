#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <gtkmm/main.h>

int main( int argc, char* argv[] ) {
  // global setup...
  Gtk::Main kit(argc, argv);

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return result;
}
