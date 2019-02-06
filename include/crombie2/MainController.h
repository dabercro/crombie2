#ifndef CROMBIE2_MAINCONTROLLER_H
#define CROMBIE2_MAINCONTROLLER_H


#include <mutex>

#include <crombie2/CutController.h>
#include <crombie2/FileController.h>
#include <crombie2/JSONModel.h>
#include <crombie2/GlobalModel.h>
#include <crombie2/PlotController.h>
#include <crombie2/PlotStyleModel.h>
#include <crombie2/Progress.h>
#include <crombie2/SimpleController.h>


namespace crombie2 {
  class MainController {
  public:
    MainController (ConfigPage& globalpage,
                    ConfigPage& jsonpage,
                    ConfigPage& plotstylepage,
                    ConfigPage& filepage,
                    ConfigPage& plotpage,
                    ConfigPage& selectionpage,
                    ConfigPage& uncertaintypage,
                    ConfigPage& jobpage);

  private:
    GlobalModel globalmodel {};
    SimpleController globalcontrol;

    JSONModel jsonmodel {};
    SimpleController jsoncontrol;

    PlotStyleModel plotstylemodel {};
    SimpleController plotstylecontrol;

    FileModel filemodel {};
    FileController filecontrol;

    PlotModel plotmodel {};
    PlotController plotcontrol;

    CutModel cutmodel {};
    CutController cutcontrol;

    ConfigPage& jobpage;

    void on_submit_job ();
    void run (unsigned num_files, const std::string& histoutdir, Progress& progress);

    std::list<Progress> progresses {};

    Gtk::HBox histsbox {};                           ///< Holds the parameters for making histograms
    Gtk::CheckButton dohists {};                     ///< Check box to activate histogram making
    Gtk::Label histslabel {"Plot output directory"}; ///< Label for the histoutput entry
    Gtk::Entry histoutput {};                        ///< Location to place histograms

    Gtk::HBox cutflowbox {};                   ///< Holds parameters for cutflow making
    Gtk::CheckButton docutflow {};             ///< Check box to activate cutflow making
    Gtk::Label cutflowlabel {"Print Cutflow"}; ///< Label for the histoutput entry

    Gtk::HBox lumibox {};
    Gtk::CheckButton dolumi {};
    Gtk::Label lumilabel {"Print Luminosity Selection"};

    Gtk::HBox reweightbox {};
    Gtk::CheckButton doreweight {};
    Gtk::Label reweight_selection_label {"Reweight Selection"};
    Gtk::Entry reweight_selection {};
    Gtk::Label reweight_plotname_label {"Plot Name"};
    Gtk::Entry reweight_plotname {};
    Gtk::Label reweight_signal_label {"Signal Entry"};
    Gtk::Entry reweight_signal {};
    Gtk::Label reweight_output_label {"Output File"};
    Gtk::Entry reweight_output {};

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
