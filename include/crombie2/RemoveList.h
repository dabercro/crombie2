#ifndef CROMBIE2_REMOVELIST_H
#define CROMBIE2_REMOVELIST_H


#include <crombie2/RemoveWrapper.h>


namespace crombie2 {
  /**
     @brief Convenience class for listing RemoveWrapper objects

     Since it's the child class of a STL container, it has no member variables, just functions.
   */
  template<class E>
    class RemoveList : public std::list<RemoveWrapper<E>> {
  public:
    RemoveList () = default;
    RemoveList (const RemoveList<E>& other) {
      for (const E& ele : other)
        append(ele);
    }

    template<typename ... Args>
      RemoveWrapper<E>& append (Args ... args) {
      return this->emplace_back(*this, args ...);
    }

  };
}


#endif
