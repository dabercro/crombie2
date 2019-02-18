#ifndef CROMBIE2_LISTMODEL_H
#define CROMBIE2_LISTMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/RemoveWrapper.h>


namespace crombie2 {
  /**
     @brief The ConfigModel that handles a list of simple ConfigTables
  */
  template<class E>
    class ListModel : public ConfigModel {

  public:

    ListModel<E> () = default;
    ListModel<E> (const ListModel<E>& other) {
      for (const E& item : other.list)
        list.emplace_back(list, item);
    }

    RemoveWrapper<E>& add () {
      return list.emplace_back(list);
    }

    std::list<RemoveWrapper<E>> list {};

  };
}


#endif
