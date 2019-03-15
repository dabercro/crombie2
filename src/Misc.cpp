#include <array>
#include <cstdlib>
#include <exception>
#include <iterator>
#include <memory>
#include <regex>
#include <sstream>

#include <gtkmm/messagedialog.h>

#include <crombie2/Misc.h>


using namespace crombie2;


Types::strings Misc::tokenize(const std::string& str) {
  std::istringstream ss {str};
  Types::strings output {
    std::istream_iterator<std::string>{ss},
    std::istream_iterator<std::string>{}
  };
  return output;
}


Types::strings Misc::split(const std::string& str, const std::string& delim) {
  Types::strings output;
  std::string::size_type prev = 0;
  for(auto pos = str.find(delim);
      pos != std::string::npos;
      prev = pos + delim.size(), pos = str.find(delim, prev))
    output.push_back(str.substr(prev, pos - prev));

  auto last = str.substr(prev);
  if (last.size())
    output.push_back(last);


  return output;
}


std::string Misc::shell(const std::string& cmd) {
  std::array<char, 128> buffer;
  std::string output;
  std::shared_ptr<FILE> pipe(popen(cmd.data(), "r"), pclose);
  if (not pipe)
    throw std::runtime_error("popen() failed");
  while(not feof(pipe.get())) {
    if (fgets(buffer.data(), 128, pipe.get()))
      output += buffer.data();
  }
  return output;
}


std::string Misc::env(const std::string& variable, const std::string& fallback) {
  auto* output = getenv(variable.data());
  if (output)
    return std::string(output);
  if (not fallback.size())
    throw std::runtime_error(std::string("Requesting non-existent variable '") + variable + "' with no fallback");
  return std::string(fallback);
}


bool Misc::confirm (const std::string& message) {

  Gtk::MessageDialog dialog (message, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_YES_NO);

  return dialog.run() == Gtk::RESPONSE_YES;

}


std::string Misc::nminus1 (const std::string& var, const std::string& cut) {

  std::regex expr{std::string("\\b") + var + "\\b\\s*[=<>]*\\s*-?[\\d\\.]+"};
  return std::regex_replace(cut, expr, "(1)");

}

void Misc::message (const std::string& primary, const std::string& secondary) {

  Gtk::MessageDialog window (primary);

  if (secondary.size())
    window.set_secondary_text(secondary);

  window.run();

}
