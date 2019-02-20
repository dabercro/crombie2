#ifndef CROMBIE2_LISTMODEL_H
#define CROMBIE2_LISTMODEL_H


#include <crombie2/ConfigModel.h>
#include <crombie2/RemoveList.h>


namespace crombie2 {
  /**
     @brief The ConfigModel that handles a list of simple ConfigTables
  */
  template<class E>
    class ListModel : public ConfigModel {

  public:

    RemoveWrapper<E>& add () {
      return list.append();
    }

    RemoveList<E> list {};

  };
}


#endif
