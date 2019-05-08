#ifndef CROMBIE2_LISTCONTROLLER_H
#define CROMBIE2_LISTCONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/ListModel.h>
#include <crombie2/Misc.h>


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
      auto& perrowlabel = perrow.get_label();
      auto& perrowentry = perrow.get_widget();

      buttonbox.pack_start(addbutton, Gtk::PACK_SHRINK);
      buttonbox.pack_start(redrawbutton, Gtk::PACK_SHRINK);
      buttonbox.pack_start(perrowlabel, Gtk::PACK_SHRINK);
      buttonbox.pack_start(perrowentry, Gtk::PACK_SHRINK);

      page.pack_start(buttonbox, Gtk::PACK_SHRINK);

      addbutton.set_border_width(10);
      redrawbutton.set_border_width(10);

      buttonbox.show();

      addbutton.show();
      redrawbutton.show();
      perrowlabel.show();
      perrowentry.show();

      addbutton.signal_clicked().
        connect(sigc::mem_fun(*this, &ListController<E>::on_add));
      redrawbutton.signal_clicked().
        connect(sigc::mem_fun(*this, &ListController<E>::redraw));

      redraw();
    }

    void redraw () override  {
      if (not unsigned(perrow)) {
        Misc::message("Items per row is set to a zero-like value!");
        return;
      }        

      drawn = 0;
      boxes.clear();
      for (auto& item : listmodel.list)
        add_table(item);
    }

  private:
    template <typename I>
      void add_table (I& item) {
      if (((drawn++) % unsigned(perrow)) == 0) {
        boxes.emplace_back();
        page.box().pack_start(boxes.back(), Gtk::PACK_SHRINK);
        boxes.back().show();
      }
      auto& box = boxes.back();
      item.draw(box);

      box.pack_start(item.remove, Gtk::PACK_SHRINK);
      item.remove.show();
    }

    void on_add () {
      add_table(listmodel.add());
    }

    ListModel<E>& listmodel;

    unsigned drawn {0};

    std::list<Gtk::HBox> boxes {};
    Gtk::HBox buttonbox {};
    Gtk::Button addbutton {"Add"};
    Gtk::Button redrawbutton {"Redraw"};
    Configurable<unsigned> perrow {"Items per row: ", 4};

  };
}


#endif
