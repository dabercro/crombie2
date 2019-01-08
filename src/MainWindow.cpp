#include <crombie2/MainWindow.h>


using namespace crombie2;


MainWindow::MainWindow ()
{
  set_default_size(1200, 800);
  set_border_width(10);

  add(book);
  book.show();
  add_page(globals);
  add_page(files);
  add_page(plots);
  add_page(selections);
  add_page(uncertainties);
  add_page(jobpage);
}


void MainWindow::add_page (ConfigPage& page) {
  book.append_page(page, page.get_label());
  page.show();
}
