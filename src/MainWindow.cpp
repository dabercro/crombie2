#include <gtkmm/main.h>

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
  book.set_tab_reorderable(page, true);
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


bool MainWindow::on_key_press_event (GdkEventKey* event) {
  if (cntrl) {

    switch(event->keyval) {

    case GDK_KEY_Page_Up:
      if (book.get_current_page())
        book.prev_page();
      else  // Assumes we have more than no pages
        book.set_current_page(book.get_n_pages() - 1);
      return false;

    case GDK_KEY_Page_Down:
      // Assumes we have more than no pages
      if (book.get_current_page() != book.get_n_pages() - 1)
        book.next_page();
      else
        book.set_current_page(0);
      return false;

    case GDK_KEY_q:
    case GDK_KEY_Q:
      Gtk::Main::quit();
      return false;

    }
  }

  if (event->keyval == GDK_KEY_Control_L)
    cntrl = true;

  return Gtk::Window::on_key_press_event(event);
}


bool MainWindow::on_key_release_event (GdkEventKey* event) {
  if (event->keyval == GDK_KEY_Control_L)
    cntrl = false;

  return Gtk::Window::on_key_press_event(event);
}
