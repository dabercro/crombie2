#ifndef CROMBIE2_MAINCONTROLLER_H
#define CROMBIE2_MAINCONTROLLER_H


#include <mutex>

#include <crombie2/AllController.h>
#include <crombie2/CompareModel.h>
#include <crombie2/CutController.h>
#include <crombie2/DatacardController.h>
#include <crombie2/FileController.h>
#include <crombie2/FitController.h>
#include <crombie2/JSONModel.h>
#include <crombie2/ListController.h>
#include <crombie2/OnTheFlyModel.h>
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

    DatacardModel datacardmodel {};
    DatacardController datacardcontrol;

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

    FitModel fitmodel {};
    FitController fitcontrol;

    CompareModel comparemodel {};
    ListController<Compare> comparecontrol;

    AllModels allmodels;
    AllController allcontrol;
    ConfigPage& jobpage;

    void on_replace_all ();

    void on_submit_job ();
    void run (unsigned num_files, const std::map<std::string, std::string>& dirs, Progress& progress);

    std::list<Progress> progresses {};

    Gtk::HBox histsbox {};                           ///< Holds the parameters for making histograms
    Gtk::CheckButton dohists {};                     ///< Check box to activate histogram making
    Gtk::Label histslabel {"Plot output directory"}; ///< Label for the histoutput entry
    Gtk::Entry histoutput {};                        ///< Location to place histograms

    Gtk::HBox datacardbox {};
    Gtk::CheckButton dodatacard {};
    Gtk::Label datacardlabel {"Datacard directory"};
    Gtk::Entry datacardoutput {};

    Gtk::HBox cutflowbox {};                   ///< Holds parameters for cutflow making
    Gtk::CheckButton docutflow {};             ///< Check box to activate cutflow making
    Gtk::Label cutflowlabel {"Print Cutflow"}; ///< Label for the histoutput entry

    Gtk::HBox lumibox {};
    Gtk::CheckButton dolumi {};
    Gtk::Label lumilabel {"Print Luminosity Selection"};

    Gtk::HBox reweightbox {};
    Gtk::CheckButton doreweight {};
    Gtk::Label reweight_label {"Do reweight"};

    Gtk::HBox fitbox {};
    Gtk::CheckButton dofit {};
    Gtk::Label fit_label {"Do fit"};

    Gtk::HBox replace_box {};
    Gtk::Entry replace1 {};
    Gtk::Label replace_label {" to "};
    Gtk::Entry replace2 {};
    Gtk::Button replace_button {"Replace All"};

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
