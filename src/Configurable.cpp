#include <crombie2/Configurable.h>


// Explicitly set these, because they're simple and because I don't know how to handle spaces
template<> void crombie2::Configurable<std::string>::set (const std::string& input) {
  value = input;
}

template<> std::string crombie2::Configurable<std::string>::get () {
  return value;
}
