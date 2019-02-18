#ifndef CROMBIE2_LISTCONTROLLER_H
#define CROMBIE2_LISTCONTROLLER_H


#include <gtkmm/buttonbox.h>

#include <crombie2/Controller.h>
#include <crombie2/ListModel.h>


namespace crombie2 {
  /**
     @brief Handles the interactions between the GUI and some ConfigModel that is just a list of repeated tables
  */
  template<class E>
    class ListController : public Controller {

  public:
    ListController (ConfigPage& page, ListModel<E>& model) :
      Controller {page, model},
      listmodel {model}
    {
      buttonbox.pack_start(addbutton, Gtk::PACK_EXPAND_PADDING);
      page.pack_start(buttonbox, Gtk::PACK_SHRINK);

      addbutton.set_border_width(10);

      buttonbox.show();
      addbutton.show();
      addbutton.signal_clicked().
        connect(sigc::mem_fun(*this, &ListController<E>::on_add));

      redraw();
    }

    void redraw () override  {
      drawn = 0;
      boxes.clear();
      for (auto& item : listmodel.list)
        add_table(item);
    }

  private:
    template <typename I>
      void add_table (I& item) {
      if (((drawn++) % 4) == 0) {
        boxes.emplace_back();
        page.box().pack_start(boxes.back(), Gtk::PACK_SHRINK);
        boxes.back().show();
      }
      auto& box = boxes.back();
      item.table.draw(box);

      box.pack_start(item.remove, Gtk::PACK_SHRINK);
      item.remove.show();
    }

    void on_add () {
      add_table(listmodel.add());
    }

    ListModel<E>& listmodel;

    unsigned drawn {0};

    std::list<Gtk::HBox> boxes {};
    Gtk::HButtonBox buttonbox {};
    Gtk::Button addbutton {"Add"};

  };
}


#endif
