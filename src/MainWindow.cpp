#include <crombie2/MainWindow.h>
#include <crombie2/Misc.h>

using namespace crombie2;


MainWindow::MainWindow ()
{
  set_default_size(1200, 800);
  set_border_width(10);

  add(book);
  book.show();
  add_page(jobpage);
  add_page(pagemap.at("globals"));
  add_page(pagemap.at("json"));
  add_page(pagemap.at("reweight"));
  add_page(pagemap.at("onthefly"));
  add_page(pagemap.at("plotstyle"));
  add_page(pagemap.at("files"));
  add_page(pagemap.at("plots"));
  add_page(pagemap.at("selections"));

}


void MainWindow::add_page (ConfigPage& page) {
  book.append_page(page, page.get_label());
  page.show();
}

std::map<std::string, ConfigPage> MainWindow::init_map () {

  std::map<std::string, ConfigPage> output {};

  output["globals"] = ConfigPage("Globals");
  output["json"] = ConfigPage("JSON Settings");
  output["reweight"] = ConfigPage("Reweight Generation");
  output["plotstyle"] = ConfigPage("Plot Style");
  output["files"] = ConfigPage("Files");
  output["plots"] = ConfigPage("Plots");
  output["selections"] = ConfigPage("Selections");
  output["onthefly"] = ConfigPage("On The Fly Reweighting");

  return output;

}
