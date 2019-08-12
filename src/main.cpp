#include <gtkmm/main.h>

#include <crombie2/MainWindow.h>

#include "TROOT.h"
#include "TStyle.h"
#include "TError.h"


int main (int argc, char *argv[])
{
  if (argc > 1)
    crombie2::ConfigModel::set_config_dir(argv[1]);

  ROOT::EnableThreadSafety();

  // Some style stuff
  gStyle->SetOptStat(0);
  gStyle->SetGridStyle(3);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetHistLineWidth(2);

  gErrorIgnoreLevel = kWarning;

  // Gtk initializtion
  Gtk::Main kit(argc, argv);

  crombie2::MainWindow window {};

  // Shows the window and returns when it is closed.
  Gtk::Main::run(window);

  return 0;
}
