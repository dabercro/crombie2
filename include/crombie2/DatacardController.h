#ifndef CROMIBE2_DATACARDCONTROLLER_H
#define CROMIBE2_DATACARDCONTROLLER_H


#include <crombie2/Controller.h>
#include <crombie2/DatacardModel.h>


namespace crombie2 {
  /**
     @brief Handles the interaction between the GUI and the DatacardModel
  */
  class DatacardController : public Controller {

  public:
    DatacardController (ConfigPage& page, DatacardModel& model);

    void redraw () override;

  private:
    DatacardModel& datacardmodel;

    ConfigTable info;

    Gtk::Label plotlabel {"Plots"};
    Gtk::VBox plots {};
    Gtk::Button plotbutton {"Add Plot"};
    Gtk::Label unclabel {"Uncertainties"};
    Gtk::VBox uncertainties {};
    Gtk::Button uncbutton {"Add Flat Uncertainty"};

    std::list<Gtk::HBox> plotboxes {};

    template <typename C>
    void draw_config (RemoveWrapper<C>& config, Gtk::VBox& vbox) {

      auto& box = plotboxes.emplace_back();

      config.draw(box);
      box.pack_start(config.remove, Gtk::PACK_SHRINK);
      config.remove.show();

      config.also_remove([&box, this] () {
        plotboxes.remove_if([&box] (auto& ele) {
          return &box == &ele;
        });
      });

      vbox.pack_start(box, Gtk::PACK_SHRINK);

      box.show();

    }

    void on_add_plot ();
    void on_add_unc ();

  };
}


#endif
