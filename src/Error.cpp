#include <crombie2/Error.h>
#include <crombie2/MainWindow.h>

#include <gtkmm/messagedialog.h>


using namespace crombie2;


void Error::Exception (const std::exception& exception, const std::string& secondary) {

  Gtk::MessageDialog message (exception.what());

  if (secondary.size())
    message.set_secondary_text(secondary);

  message.run();

}
