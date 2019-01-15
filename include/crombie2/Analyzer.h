#ifndef CROMBIE2_ANALYZER_H
#define CROMBIE2_ANALYZER_H


#include <crombie2/Tree.h>


namespace crombie2 {
  /**
     @brief Abstract class that every analyzer that reads from a Tree should implement

     Job objects hold a collection of analyzers that it communicates to through this interface.
  */
  class Analyzer {
  public:
    virtual ~Analyzer () = default;

    /// Request formulas and any other objects from the Tree
    virtual void make_requests (Tree& tree) = 0;

    /// Called by the Job every time a new Tree entry is loaded
    virtual void notify () = 0;

  };
}

#endif
