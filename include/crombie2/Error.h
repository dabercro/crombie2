#ifndef CROMBIE2_ERROR_H
#define CROMBIE2_ERROR_H


#include <exception>
#include <string>


namespace crombie2 {
  namespace Error {

    /**
       Displays an exception message.
       The calling function should handle the exception.
    */
    void Exception (const std::exception& exception, const std::string& secondary = "");

  }
}


#endif
