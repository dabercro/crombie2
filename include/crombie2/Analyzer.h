#ifndef CROMBIE2_ANALYZER_H
#define CROMBIE2_ANALYZER_H


#include <crombie2/Tree.h>


namespace crombie2 {
  class Analyzer {
  public:
    virtual ~Analyzer ();

    virtual void make_requests (Tree& tree) = 0;

    virtual void notify () = 0;

  };
}

#endif
