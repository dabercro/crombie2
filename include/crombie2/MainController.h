#ifndef CROMBIE2_MAINCONTROLLER_H
#define CROMBIE2_MAINCONTROLLER_H


#include <mutex>

#include <crombie2/CutController.h>
#include <crombie2/FileController.h>
#include <crombie2/GlobalModel.h>
#include <crombie2/PlotController.h>
#include <crombie2/PlotStyleModel.h>
#include <crombie2/Progress.h>
#include <crombie2/SimpleController.h>


namespace crombie2 {
  class MainController {
  public:
    MainController (ConfigPage& globalpage,
                    ConfigPage& plotstylepage,
                    ConfigPage& filepage,
                    ConfigPage& plotpage,
                    ConfigPage& selectionpage,
                    ConfigPage& uncertaintypage,
                    ConfigPage& jobpage);

  private:
    GlobalModel globalmodel {};
    SimpleController globalcontrol;

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
    void run (unsigned num_files, Progress& progress);

    std::list<Progress> progresses {};

    Gtk::HBox histsbox {};                           ///< Holds the parameters for making histograms
    Gtk::CheckButton dohists {};                     ///< Check box to activate histogram making
    Gtk::Label histslabel {"Plot output directory"}; ///< Label for the histoutput entry
    Gtk::Entry histoutput {};                        ///< Location to place histograms

    Gtk::HBox cutflowbox {};                   ///< Holds parameters for cutflow making
    Gtk::CheckButton docutflow {};             ///< Check box to activate cutflow making
    Gtk::Label cutflowlabel {"Print Cutflow"}; ///< Label for the histoutput entry

    Gtk::HButtonBox submitbox {};
    Gtk::Button button {"Submit"};

  };
}


#endif
