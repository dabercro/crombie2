#include <gtkmm/messagedialog.h>

#include <crombie2/Error.h>


using namespace crombie2;


void Error::Exception (const std::string& primary, const std::string& secondary) {

  Gtk::MessageDialog message (primary);

  if (secondary.size())
    message.set_secondary_text(secondary);

  message.run();

}


void Error::Exception (const std::exception& exception, const std::string& secondary) {

  Exception(exception.what(), secondary);

}
