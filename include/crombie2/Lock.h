#ifndef CROMBIE2_LOCK_H
#define CROMBIE2_LOCK_H


#include <mutex>


namespace crombie2 {
  /**
     @brief a lock that accesses the same mutex.

     This should be constructed in some scope where you do a bunch of ROOT stuff.
     Everything else attempts to be threadsafe.
  */
  class Lock {
  public:
    Lock ();

  private:
    std::unique_lock<std::mutex> lock;

  };
}


#endif
