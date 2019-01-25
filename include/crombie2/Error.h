#ifndef CROMBIE2_ERROR_H
#define CROMBIE2_ERROR_H


#include <exception>
#include <string>


namespace crombie2 {
  namespace Error {

    /// Displays messages for user to see error
    void Exception (const std::string& primary, const std::string& secondary = "");

    /**
       Displays an exception message as primary.
       The calling function should handle the exception.
    */
    void Exception (const std::exception& exception, const std::string& secondary = "");


  }
}


#endif
