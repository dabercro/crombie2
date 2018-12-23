#include <crombie2/MainWindow.h>

using namespace crombie2;

MainWindow::MainWindow ()
{
  add(book);
  book.show();
  add_page(selections);
}


void MainWindow::add_page (ConfigPage& page) {
  book.append_page(page, page.get_label());
  page.show();
}
