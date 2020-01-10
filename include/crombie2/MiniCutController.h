#ifndef CROMBIE2_MINICUTCONTROLLER_H
#define CROMBIE2_MINICUTCONTROLLER_H


#include <crombie2/ConfigTable.h>
#include <crombie2/RemoveWrapper.h>


namespace crombie2 {
  /**
     @brief Handles the GUI interaction for each CutString that is part of the CutModel
  */
  template<typename C>
  class MiniCutController {
  public:

    explicit MiniCutController (RemoveWrapper<C>& cutstring);

    void draw (Gtk::Box& page) {

      page.pack_start(cutstring.remove, Gtk::PACK_SHRINK);
      cutstring.remove.show();

      page.pack_start(box, Gtk::PACK_SHRINK);

      labeltable.draw(labellist);
      cuttable.draw(cutlist);

      box.pack_start(labellist, Gtk::PACK_SHRINK);
      box.pack_start(cutlist, Gtk::PACK_SHRINK);
      cutlist.pack_end(addbutton, Gtk::PACK_SHRINK);
      addbutton.set_border_width(10);

      box.show();
      labellist.show();
      cutlist.show();
      addbutton.show();

      addbutton.signal_clicked().
        connect(sigc::mem_fun(*this, &MiniCutController::on_add_cut));

    }

  private:
    RemoveWrapper<C>& cutstring;
    ConfigTable labeltable;
    ConfigTable cuttable {};

    void on_add_cut () {

      auto& cut = cutstring.add_cut();

      cuttable.add_conf(&cut);
      cuttable.redraw();

    }

    void init () {
      auto& cuts = cutstring.get_cuts();
      if (not cuts.size())
        cutstring.add_cut();
      for (auto& cut : cuts)
        cuttable.add_conf(&cut);
    }

    Gtk::HBox box {};
    Gtk::VBox labellist {};
    Gtk::VBox cutlist {};
    Gtk::Button addbutton {"Add"};

  };

}


#endif
