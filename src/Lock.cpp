#include <mutex>

#include <crombie2/Lock.h>


using namespace crombie2;


namespace {

  std::mutex rootlock {};

}


Lock::Lock () :
  lock {rootlock} {}
