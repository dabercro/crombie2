#ifndef CROMBIE2_CUTSCONTROLLER_H
#define CROMBIE2_CUTSCONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/MiniCutController.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the CutModel
  */
  template<typename C>
  class CutsController : public Controller {
  public:
    CutsController (ConfigPage& page, C& model) :
      Controller {page, model},
      cutmodel {model}
    {

      buttonbox.pack_start(labelentry, Gtk::PACK_SHRINK);
      buttonbox.pack_start(addcutbutton, Gtk::PACK_SHRINK);

      addcutbutton.set_border_width(10);

      labelentry.show();
      addcutbutton.show();
      buttonbox.show();

      page.pack_start(buttonbox, Gtk::PACK_SHRINK);

      addcutbutton.signal_clicked().
        connect(sigc::mem_fun(*this, &CutsController::on_add_cut));

      // Draws the stuff loaded by the Controller constructor
      redraw();

    }

    void redraw () override;

  protected:

    void on_add_cut () {
      add_cut(cutmodel.add_cutstring(labelentry.get_chars(0, -1)));
    }

    void add_cut (RemoveWrapper<typename C::cutstype>& cutstring)  {

      if (((numcuts++) % 1) == 0)
        page.draw(cutboxes.emplace_back());

      auto& mini = minicontrollers.emplace_back(cutstring);
      mini.draw(cutboxes.back());

      cutstring.also_remove([&mini, this] () {
        minicontrollers.remove_if([&mini] (auto& ele) {
          return &mini == &ele;
          });
      });

    }

    C& cutmodel;

    unsigned numcuts {0};

    std::list<Gtk::HBox> cutboxes {};
    Gtk::HBox selectionbox {};

    Gtk::HBox buttonbox {};
    Gtk::Entry labelentry {};
    Gtk::Button addcutbutton {"Add Cut"};

    std::list<MiniCutController<typename C::cutstype>> minicontrollers {};

  };
}


#endif
