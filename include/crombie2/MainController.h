#ifndef CROMBIE2_MAINCONTROLLER_H
#define CROMBIE2_MAINCONTROLLER_H


#include <mutex>

#include <crombie2/AllController.h>
#include <crombie2/CutController.h>
#include <crombie2/FileController.h>
#include <crombie2/JSONModel.h>
#include <crombie2/GlobalModel.h>
#include <crombie2/ListController.h>
#include <crombie2/OnTheFlyModel.h>
#include <crombie2/PlotModel.h>
#include <crombie2/PlotStyleModel.h>
#include <crombie2/Progress.h>
#include <crombie2/ReweightModel.h>
#include <crombie2/SimpleController.h>


namespace crombie2 {
  class MainController {
  public:
    MainController (std::map<std::string, ConfigPage>& pagemap,
                    ConfigPage& jobpage);

  private:
    GlobalModel globalmodel {};
    SimpleController globalcontrol;

    JSONModel jsonmodel {};
    SimpleController jsoncontrol;

    ReweightModel reweightmodel {};
    SimpleController reweightcontrol;

    OnTheFlyModel ontheflymodel {};
    ListController<ReweightReader> ontheflycontrol;

    PlotStyleModel plotstylemodel {};
    SimpleController plotstylecontrol;

    FileModel filemodel {};
    FileController filecontrol;

    PlotModel plotmodel {};
    ListController<Plot> plotcontrol;

    CutModel cutmodel {};
    CutController cutcontrol;

    AllModels allmodels;
    AllController allcontrol;
    ConfigPage& jobpage;

    void on_submit_job ();
    void run (unsigned num_files, const std::string& histoutdir, Progress& progress);

    std::list<Progress> progresses {};

    Gtk::HBox histsbox {};                           ///< Holds the parameters for making histograms
    Gtk::CheckButton dohists {};                     ///< Check box to activate histogram making
    Gtk::Label histslabel {"Plot output directory"}; ///< Label for the histoutput entry
    Gtk::Entry histoutput {};                        ///< Location to place histograms
    Gtk::Label histnorm_label {"Normalize"};
    Gtk::CheckButton histnorm {};

    Gtk::HBox cutflowbox {};                   ///< Holds parameters for cutflow making
    Gtk::CheckButton docutflow {};             ///< Check box to activate cutflow making
    Gtk::Label cutflowlabel {"Print Cutflow"}; ///< Label for the histoutput entry

    Gtk::HBox lumibox {};
    Gtk::CheckButton dolumi {};
    Gtk::Label lumilabel {"Print Luminosity Selection"};

    Gtk::HBox reweightbox {};
    Gtk::CheckButton doreweight {};
    Gtk::Label reweight_norm_label {"Normalize before reweight"};
    Gtk::CheckButton reweight_norm {};

    Gtk::HButtonBox submitbox {};
    Gtk::Button button {"Submit"};

    /**
       @brief Allows easy adding of controls to the "Jobs" page.

       Adds a widget into a box, adds that box to the "Jobs" ConfigPage, and then shows the box and widget.
       This terminates the variadic template function with the same name.
    */
    void setup_controls (Gtk::HBox& box, Gtk::Widget& to_add);

    /// Allows easy adding of controls to the "Jobs" page.
    template <typename ... Args> void setup_controls (Gtk::HBox& box, Gtk::Widget& to_add,
                                                      Args& ... more_widgets) {
      box.pack_start(to_add, Gtk::PACK_SHRINK);
      to_add.show();
      setup_controls(box, more_widgets ...);
    }

  };
}


#endif
