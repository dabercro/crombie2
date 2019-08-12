#include <gtkmm/main.h>

#include <crombie2/MainWindow.h>

using namespace crombie2;


MainWindow::MainWindow ()
{
  set_default_size(1200, 800);
  set_border_width(10);

  add(book);
  book.show();
  add_page(jobpage);
  add_page(pagemap.at("globals"));
  add_page(pagemap.at("selections"));
  add_page(pagemap.at("plots"));
  add_page(pagemap.at("files"));
  add_page(pagemap.at("plotstyle"));
  add_page(pagemap.at("datacards"));
  add_page(pagemap.at("fits"));
  add_page(pagemap.at("compare"));
  add_page(pagemap.at("onthefly"));
  add_page(pagemap.at("reweight"));
  add_page(pagemap.at("json"));

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
  output["datacards"] = ConfigPage("Datacard");
  output["files"] = ConfigPage("Files");
  output["fits"] = ConfigPage("Fits");
  output["plots"] = ConfigPage("Plots");
  output["compare"] = ConfigPage("Comparisons");
  output["selections"] = ConfigPage("Selections");
  output["onthefly"] = ConfigPage("On The Fly Reweighting");

  return output;

}


bool MainWindow::on_key_press_event (GdkEventKey* event) {
  if (cntrl) {

    switch(event->keyval) {

    case GDK_KEY_Page_Up:
    case GDK_KEY_braceleft:
      if (book.get_current_page())
        book.prev_page();
      else  // Assumes we have more than no pages
        book.set_current_page(book.get_n_pages() - 1);
      return false;

    case GDK_KEY_Page_Down:
    case GDK_KEY_braceright:
      // Assumes we have more than no pages
      if (book.get_current_page() != book.get_n_pages() - 1)
        book.next_page();
      else
        book.set_current_page(0);
      return false;

    case GDK_KEY_q:
    case GDK_KEY_Q:
    case GDK_KEY_w:
    case GDK_KEY_W:
      Gtk::Main::quit();
      return false;

    case GDK_KEY_Down:
      current_page().scroll(ConfigPage::Scroll::DOWN);
      return false;

    case GDK_KEY_Up:
      current_page().scroll(ConfigPage::Scroll::UP);
      return false;

    case GDK_KEY_Left:
      current_page().scroll(ConfigPage::Scroll::LEFT);
      return false;

    case GDK_KEY_Right:
      current_page().scroll(ConfigPage::Scroll::RIGHT);
      return false;

    }
  }

  if (is_cntrl(event))
    cntrl = true;

  return Gtk::Window::on_key_press_event(event);
}


bool MainWindow::on_key_release_event (GdkEventKey* event) {
  if (is_cntrl(event))
    cntrl = false;

  return Gtk::Window::on_key_press_event(event);
}


ConfigPage& MainWindow::current_page () {

  auto* output = static_cast<ConfigPage*>(book.get_nth_page(book.get_current_page()));
  return *output;

}


bool MainWindow::is_cntrl (const GdkEventKey* event) const {

  return (event->keyval == GDK_KEY_Control_L or event->keyval == GDK_KEY_Meta_L or
          event->keyval == GDK_KEY_Control_R or event->keyval == GDK_KEY_Meta_R);

}
